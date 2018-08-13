#include "Spaceship.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

float Spaceship::getX()
{
	return x;
}

float Spaceship::getY()
{
	return y;
}

void Spaceship::render(float xOffset, float yOffset)
{
	if (!isDead) {
		al_draw_rotated_bitmap(texture, al_get_bitmap_width(texture) / 2, al_get_bitmap_height(texture) / 2, x + xOffset, y + yOffset, rotation, 0);
	}
	std::string s = "universe_radius: ";
	s += std::to_string((int)core->getRadius());
	al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, s.c_str());

	s = "space in ship: ";
	s += std::to_string((int)space);
	al_draw_text(font, al_map_rgb(255, 255, 255), 10, 50, 0, s.c_str());

	s = "fuel: ";
	s += std::to_string((int)fuel);
	al_draw_text(font, al_map_rgb(255, 255, 255), 10, 90, 0, s.c_str());

	s = "crew: ";
	s += std::to_string((int)crewSize);
	al_draw_text(font, al_map_rgb(255, 255, 255), 10, 130, 0, s.c_str());

	if (connectedPlanet) {
		if (shipinterface.collectOil) {
			al_play_sample_instance(buttonPress);
			space -= connectedPlanet->getOil();
			if (space > 0) {
				fuel += connectedPlanet->getOil();
				connectedPlanet->setOil(0);
			}
			else {
				space += connectedPlanet->getOil();
				fuel += space;
				connectedPlanet->setOil(connectedPlanet->getOil() - space);
				space = 0;
			}
		}
		shipinterface.render(connectedPlanet->getType());
		s = "Pickup or drop";
		al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1095, 15, 0, s.c_str());
		s = " crew?";
		al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1095, 35, 0, s.c_str());
		s = std::to_string(connectedPlanet->getHumanCount()) + " lifeforms";
		al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1095, 55, 0, s.c_str());
		if (connectedPlanet->getType() == 0 || connectedPlanet->getType() == 2 || connectedPlanet->getType() == 4 || connectedPlanet->getType() == 6) {
			s = "fuel: " + std::to_string(connectedPlanet->getOil());
			al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1095, 170, 0, s.c_str());
		}
	}

	if (coreConnected) {
		shipinterface.render(100);
		s = "Core Fuel: ";
		s += std::to_string(core->getFuel());
		al_draw_text(smallFont, al_map_rgb(255, 255, 255), 1095, 15, 0, s.c_str());
	}

	minimap.render();
	minimap.update(pManager, x, y, xOffset, yOffset);
	for (int i = 0; i < particles.size(); i++) {
		particles[i].render(xOffset, yOffset);
	}
	if (isDead) {
		al_draw_bitmap(deadTexture, 0, 0, 0);
	}
}

void Spaceship::update()
{
	for (int i = 0; i < particles.size(); i++) {
		particles[i].update();
		if (particles[i].getSize() <= 0) {
			particles.erase(particles.begin() + i);
		}
	}
	ALLEGRO_KEYBOARD_STATE state;
	al_get_keyboard_state(&state);
	if (al_key_down(&state, ALLEGRO_KEY_LEFT) && fuel > 0 && !connectedPlanet && !coreConnected) {
		this->rotation -= 0.05;
		fuel -= 1;
		space++;
		particles.push_back(Particle(x, y, -rotation));
	}
	else {
		if (al_key_down(&state, ALLEGRO_KEY_RIGHT) && fuel > 0 && !connectedPlanet && !coreConnected) {
			this->rotation += 0.05;
			fuel -= 1;
			space++;
			particles.push_back(Particle(x, y, -rotation));
		}
		else {
			if (al_key_down(&state, ALLEGRO_KEY_SPACE)) {
				connectedPlanet = NULL;
				coreConnected = false;
			}
		}
	}

	
	auto planets = pManager->get_planets();
	if (!this->connectedPlanet) {
		if (!coreConnected) {
			x = x + sin(rotation) * 4;
			y = y - cos(rotation) * 4;

			for (int i = 0; i < planets.size(); i++) {
				if (Collision(*planets[i])) {
					this->connectedPlanet = planets[i];
					//orbitAngle = (y - (connectedPlanet->getY() + (connectedPlanet->getWidth() / 2))) / (x - (connectedPlanet->getX() + (connectedPlanet->getWidth() / 2)));
				}

			}
		}
	}
	else { 
		int pradius = connectedPlanet->getWidth() / 2;
		//orbitAngle += 0.02;
		orbitAngle += 0.04;
		float rico = (y - (connectedPlanet->getY()+pradius)) / (x - (connectedPlanet->getX()+pradius));
		rotation = atan(rico);
		if (x < connectedPlanet->getX() + pradius) {
			rotation -= 179;
		}
		x = connectedPlanet->getX() + 100 * sin(orbitAngle) + pradius;
		y = connectedPlanet->getY() + 100 * cos(orbitAngle) + pradius;

		shipinterface.update();
		if (shipinterface.transfer) {
			al_play_sample_instance(buttonPress);
			if (shipinterface.drop == false && crewSize < 30 && connectedPlanet->getHumanCount() > 0) {
				space -= 6;
				crewSize++;
				connectedPlanet->setHumanCount(connectedPlanet->getHumanCount() - 1);
			}
			else {
				if (shipinterface.drop == true && crewSize > 0) {
					space += 6;
					crewSize--;
					connectedPlanet->setHumanCount(connectedPlanet->getHumanCount() + 1);
				}
			}
			if (crewSize > 30) { crewSize = 30; }
		}
	}

	if (pow(x - 640, 2) + pow(y - 360, 2) < pow(core->getPradius(), 2) && !connectedPlanet) {
		coreConnected = true;
	}

	if (coreConnected) {
		//int pradius = core->getPradius();
		shipinterface.update();
		if (shipinterface.collectCoreOil) {
			al_play_sample_instance(buttonPress);
			if (shipinterface.drop == true && core->getFuel() > 0) {
				core->setFuel(core->getFuel()-1);
				fuel++;
			}
			else {
				if (shipinterface.drop == false && fuel > 0) {
					core->setFuel(core->getFuel() + 1);
					fuel--;
				}
			}
		}
		orbitAngle += 0.04;
		float rico = (y - (360)) / (x - (640));
		rotation = atan(rico);
		if (x < 640) {
			rotation -= 179;
		}
		x = 640 + 100 * sin(orbitAngle);
		y = 360 + 100 * cos(orbitAngle);

	}


	if (((640 - x)*(640 - x) + (360 - y)*(360 - y)) > pow(core->getRadius(), 2)) {
		isDead = true;
	}
}

void Spaceship::setPmanager(Planetmanager *p)
{
	pManager = p;
}

bool Spaceship::Collision(Planet p)
{
	int pR = p.getWidth() / 2;
	int pX = p.getX() + pR;
	int pY = p.getY() + pR;

	if ((pR + radius)*(pR+radius) > ((pX-x)*(pX-x) + (pY-y)*(pY-y))) {
		return true;
	}
	return false;
}

void Spaceship::setCore(Core * c)
{
	this->core = c;
}

Spaceship::Spaceship()
{
	tmp = al_load_sample("sound/button.wav");
	buttonPress = al_create_sample_instance(tmp);
	al_set_sample_instance_playmode(buttonPress, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(buttonPress, al_get_default_mixer());

	this->deadTexture = al_load_bitmap("Images/dead.png");
	this->texture = al_load_bitmap("Images/Spaceship.png");
	if (!texture) {
		al_show_native_message_box(al_get_current_display(), "error", "spaceship texture not found", 0, 0, 0);
	}
	this->width = al_get_bitmap_width(texture);
	this->height = al_get_bitmap_height(texture);
	this->rotation = 0;
	this->x = 640;
	this->y = 360;
	radius = 25;
	orbitAngle = 0;
	isDead = false;
	fuel = 80;
	crewSize = 0;
	space = 200;
	coreConnected = false;

	shipinterface = ShipInterface(1080, 0);
	minimap = Minimap();

	font = al_load_font("aliee13.ttf", 24, 0);
	smallFont = al_load_font("aliee13.ttf", 20, 0);
}


Spaceship::~Spaceship()
{
}
