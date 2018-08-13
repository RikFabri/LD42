#pragma once
#include "Planet.h"
#include <array>
#include "Core.h"

class Planetmanager
{
private:
	ALLEGRO_FONT *font;
	Core *core;
	std::array<Planet*, 40> planets;
public:
	std::array<Planet*, 40> get_planets();
	void update();
	void render(float xOffset, float yOffset);
	void setCore(Core *c);
	Planetmanager();
	~Planetmanager();
};

