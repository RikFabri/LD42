#include "Planetmanager.h"



std::array<Planet*, 40> Planetmanager::get_planets()
{
	return planets;
}

void Planetmanager::update()
{
	for (int i = 0; i < planets.size(); i++) {
		planets[i]->update();
	}
}

void Planetmanager::render(float xOffset, float yOffset)
{
	for (int i = 0; i < planets.size(); i++) {
		planets[i]->render(xOffset, yOffset);
	}
	if (core->done) {
		al_draw_text(font, al_map_rgb(255, 255, 255), 640, 10, ALLEGRO_ALIGN_CENTER, "You win!");
	}
}

void Planetmanager::setCore(Core *c)
{
	this->core = c;
	for (int i = 0; i < planets.size(); i++) {
		planets[i]->setCore(c);
	}
}

Planetmanager::Planetmanager()
{
	font = al_load_font("aliee13.ttf", 60, 0);
	for (int i = 0; i < planets.size(); i++) {
		planets[i] = new Planet();
	}
}


Planetmanager::~Planetmanager()
{
}
