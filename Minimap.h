#pragma once
#include "Planetmanager.h"
#include "allegro5/allegro_primitives.h"
#include <iostream>

class Minimap
{
private:
	ALLEGRO_BITMAP *background;
public:
	void render();
	void update(Planetmanager *pm, float sx, float sy, float xOffset, float yOffset);
	Minimap();
	~Minimap();
};

