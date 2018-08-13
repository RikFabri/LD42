#include "Endcircle.h"



void Endcircle::render(int xOffset, int yOffset)
{
	al_draw_circle(640+xOffset, 360+yOffset, size, al_map_rgba(0+(size),242,255, 255-(size)), 1);
}

void Endcircle::update()
{
	size+=2;
	if (size > 900) {
		size = 20;
	}
}

Endcircle::Endcircle(int s)
{
	size = s;
}


Endcircle::~Endcircle()
{
}
