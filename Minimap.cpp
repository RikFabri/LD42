#include "Minimap.h"



void Minimap::render()
{
	al_draw_bitmap(background, 1280-220, 545, 0);
	al_draw_filled_rectangle(1080, 570, 1280, 720, al_map_rgb(0, 0, 0));
}

void Minimap::update(Planetmanager *pm, float sx, float sy, float xOffset, float yOffset)
{
	float xFrac = 30.0 / 1280.0;
	float yFrac = 30.0 / 720.0;
	xOffset += 3300;
	yOffset += 1500;
	auto planets = pm->get_planets();
	for (auto it : planets) {
		float x = (it->getX() + xOffset)*xFrac + 1080;
		float y = (it->getY() + yOffset)*yFrac + 570;
		if (x > 1080 && y > 570) {
			al_draw_filled_rectangle(x, y, x + 5, y + 5, al_map_rgb(255, 0, 0));
		}
	}
	al_draw_filled_rectangle((sx + xOffset)*xFrac + 1080, (sy + yOffset)*yFrac + 570, (sx + xOffset)*xFrac + 1080 + 5, (sy + yOffset)*yFrac + 570 + 5, al_map_rgb(255, 255, 255));
	float cx = (640 + xOffset)*xFrac + 1080;
	float cy = (360 + yOffset)*yFrac + 570;
	if (cx > 1080 && cy > 570) {
		al_draw_filled_rectangle(cx, cy, cx + 5, cy + 5, al_map_rgb(0, 0, 255));
	}
}

Minimap::Minimap()
{
	background = al_load_bitmap("Images/minimap.png");
}


Minimap::~Minimap()
{
}
