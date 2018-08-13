#pragma once
#include "Spaceship.h"
#include "Core.h"
#include "Planetmanager.h"
#include "Camera.h"

class Game
{
private:
	Camera cam;
	ALLEGRO_DISPLAY * display;
	Spaceship *spaceship;
	ALLEGRO_COLOR black;
	Core *core;
	Planetmanager planetmanager;
public:
	void update();
	void render();
	Game();
	~Game();
};

