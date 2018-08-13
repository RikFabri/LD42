#include "Particle.h"



float Particle::getSize()
{
	return size;
}

void Particle::update()
{
	this->size-= 0.1;
	x = x + sin(rotation) * speed;
	y = y + cos(rotation) * speed;
}

void Particle::render(float xOffset, float yOffset)
{
	al_draw_filled_rectangle(x+xOffset, y+yOffset, x+size+xOffset, y+size+yOffset, al_map_rgb(0,242,255-size*2));
}

Particle::Particle(int x, int y, int rotation){
	this->x = x;
	this->y = y;
	this->rotation = rotation;
	this->rotation -= (rand() % 20 - 10)/10;
	this->size = 20;
	this->speed = (rand() % 4 - 2)/10.0;
}


Particle::~Particle()
{
}
