#pragma once
#include "allegro5/allegro.h"
#include <iostream>


class ShipInterface
{
private:
	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * greenbg;
	ALLEGRO_EVENT_QUEUE *EQ;
	int x, y;
	int width, height;
public:
	bool collectOil;
	bool collectCoreOil;
	bool transfer;
	bool drop;
	void clearEvents();
	void update();
	void render(int ptype);
	ShipInterface();
	ShipInterface(int x, int y);
	~ShipInterface();
};

