#include "ShipInterface.h"



void ShipInterface::clearEvents()
{
	//al_flush_event_queue(EQ);
}

void ShipInterface::update()
{
	transfer = false;
	collectOil = false;
	collectCoreOil = false;
	ALLEGRO_EVENT E;
	while (al_get_next_event(EQ, &E)) {
		if (E.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (E.mouse.x > x && E.mouse.x < x+width && E.mouse.y > y && E.mouse.y < y+height) {
				if (E.mouse.y > 95) {
					if (E.mouse.x > x + (width / 2)) {
						drop = true;
						transfer = true;
						collectCoreOil = true;
					}
					else {
						transfer = true;
						drop = false;
						collectCoreOil = true;
					}
				}
			}
			else {
				if (E.mouse.x > x && E.mouse.x < x+width && E.mouse.y > 204 && E.mouse.y < 150+96) {
					collectOil = true;
				}
			}
		}
	}
}

void ShipInterface::render(int ptype)
{
	al_draw_bitmap(background, 1280 - 200, 0, 0);
	if (ptype == 0 || ptype == 2 || ptype == 4 || ptype == 6) {
		al_draw_bitmap(greenbg, 1280 - 200, 150, 0);
	}
}

ShipInterface::ShipInterface()
{
}

ShipInterface::ShipInterface(int x, int y)
{
	//ShipInterface();
	collectOil = false;
	EQ = al_create_event_queue();
	al_register_event_source(EQ, al_get_mouse_event_source());
	background = al_load_bitmap("Images/UIbg.png");
	greenbg = al_load_bitmap("Images/greenUI.png");
	this->x = x;
	this->y = y;
	this->width = al_get_bitmap_width(background);
	this->height = al_get_bitmap_height(background);
	drop = false;
	transfer = false;
}


ShipInterface::~ShipInterface()
{
}
