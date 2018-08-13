#pragma once
#include "allegro5/allegro_primitives.h"

class Endcircle
{
public:
	int size;
	void render(int xOffset, int yOffset);
	void update();
	Endcircle(int s);
	~Endcircle();
};

