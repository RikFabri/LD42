#include "Planet.h"
#include <iostream>


int Planet::getOil()
{
	return oil;
}

void Planet::setOil(int o)
{
	oil = o;
}

void Planet::setHumanCount(int c)
{
	humanCount = c;
}

int Planet::getHumanCount()
{
	return humanCount;
}

int Planet::getWidth()
{
	return width;
}

int Planet::getHeight()
{
	return height;
}

int Planet::getType()
{
	return ptype;
}

float Planet::getX()
{
	return x;
}

float Planet::getY()
{
	return y;
}

void Planet::render(float xOffset, float yOffset)
{
	if (!isDead) {
		al_draw_bitmap(texture, x + xOffset, y + yOffset, 0);
		if (humanCount) {
			al_draw_bitmap(humanMark, x + xOffset, y-80 + yOffset, 0);
		}
	}
}

void Planet::update()
{
	if (!isDead) {
		if (!core->done) {
			int posneg = 0;
			if (x > (640 - width / 2)) { posneg = -1; }
			else { posneg = 1; }
			float degree = atan(((360 - height / 2) - y) / ((640 - width / 2) - x));
			x = posneg * cos(degree) * 0.5 + x;
			y = posneg * sin(degree) * 0.5 + y;
		}
		int pradius = width / 2;
		if (pow(core->getRadius() - pradius, 2) < (pow(640-(x+pradius), 2) + pow(360-(y+pradius), 2)) ||
			(pow(640 - (x + pradius), 2) + pow(360 - (y + pradius), 2)) < pow(width, 2)
			) {
			isDead = true;
			x = -3000;
			y = -3000;
		}
		if (ptype == 0 || ptype == 2 || ptype == 4 || ptype==6) {
			counter+=2;
			int hcount = humanCount;
			if (hcount > 29) { hcount = 29; }
			if (counter % (211-(hcount*7)) == 0 && humanCount > 0) {
				counter = 0;
				oil++;
			} 
		}
	}
}

void Planet::setCore(Core * c)
{
	this->core = c;
}

Planet::Planet()
{
	counter = 0;
	std::string name = "Images/Planet_";
	ptype = rand() % 7;
	name = name + std::to_string(ptype) + ".png";
	//std::cout << name << std::endl;
	texture = al_load_bitmap(name.c_str());
	humanMark = al_load_bitmap("Images/humanMark.png");
	if (!texture || !humanMark) {
		al_show_native_message_box(al_get_current_display(), "error", "planet texture not found", 0, 0, 0);
	}
	x = rand() % 14000 - 7000;
	y = rand() % 14000 - 7000;

	if (rand() % 100 > 50) {
		if (ptype == 1) {
			humanCount = rand() % 4;
		}
		else {
			humanCount = rand() % 10;
		}
	}
	
	width = al_get_bitmap_width(texture);
	height = al_get_bitmap_height(texture);

	isDead = false;
}


Planet::~Planet()
{
}
