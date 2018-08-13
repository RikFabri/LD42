#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

class Particle
{
private:
	int x, y;
	float size;
	float rotation;
	float speed;
public:
	float getSize();
	void update();
	void render(float xOffset, float yOffset);
	Particle(int x, int y, int rotation);
	~Particle();
};

