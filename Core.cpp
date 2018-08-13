#include "Core.h"



int Core::getFuel()
{
	return fuel;
}

void Core::setFuel(int f)
{
	fuel = f;
}

int Core::getPradius()
{
	return al_get_bitmap_width(texture)/2;
}

void Core::update()
{
	if (universe_radius > 0) {
		universe_radius -= 1;
	}
	if (fuel >= 100) {
		universe_radius = 10000;
	}
	if (done) {
		for (int i = 0; i < 20; i++) {
			circles[i].update();
		}
	}
}

void Core::render(float xOffset, float yOffset)
{
	al_draw_filled_circle(x + al_get_bitmap_width(texture) / 2 + xOffset, y + al_get_bitmap_height(texture) / 2 + yOffset, universe_radius, al_map_rgb(20, 0, 20));
	al_draw_bitmap(texture, x + xOffset, y + yOffset, 0);
	//al_draw_circle(x + al_get_bitmap_width(texture)/2, y + al_get_bitmap_height(texture) / 2, universe_radius, al_map_rgb(255, 0, 0), 1);
	if (done) {
		for (int i = 0; i < 20; i++) {
			circles[i].render(xOffset, yOffset);
		}
	}
	if (fuel >= 100 && !done) {
		for (int i = 0; i < 20; i++) {
			circles.push_back(Endcircle(i));
		}
		done = true;
	}
}

int Core::getX()
{
	return x;
}

int Core::getY()
{
	return y;
}

float Core::getRadius()
{
	return universe_radius;
}

Core::Core()
{
	texture = al_load_bitmap("Images/core.png");
	int dWidth = al_get_display_width(al_get_current_display());
	int dHeight = al_get_display_height(al_get_current_display());
	int tWidth = al_get_bitmap_width(texture);
	int tHeight = al_get_bitmap_height(texture);
	winCsize = 20;
	x = (dWidth - tWidth) / 2;
	y = (dHeight - tHeight) / 2;
	universe_radius = 7000;
	fuel = 0;
	done = false;
}

Core::~Core()
{
}
