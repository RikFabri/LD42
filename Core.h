#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "Endcircle.h"
#include <vector>

class Core
{
private:
	int x, y;
	float universe_radius;
	ALLEGRO_BITMAP *texture;
	int fuel;
	int winCsize;
	std::vector<Endcircle> circles;
public:
	bool done;
	int getFuel();
	void setFuel(int f);
	int getPradius();
	void update();
	void render(float xOffset, float yOffset);
	int getX();
	int getY();
	float getRadius();
	Core();
	~Core();
};

