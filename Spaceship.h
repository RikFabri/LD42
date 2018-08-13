#pragma once
#include "allegro5/allegro_image.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_audio.h"
#include <iostream>
#include "Planetmanager.h"
#include "Core.h"
#include "ShipInterface.h"
#include "Minimap.h"
#include "Particle.h"

class Spaceship
{
private:
	ALLEGRO_SAMPLE * tmp;
	ALLEGRO_SAMPLE_INSTANCE *buttonPress;

	ALLEGRO_BITMAP *deadTexture;
	ALLEGRO_FONT *font;
	ALLEGRO_FONT *smallFont;
	ALLEGRO_BITMAP *texture;
	float x, y;
	float rotation;
	int width, height;
	int radius;
	Planetmanager *pManager;
	Planet *connectedPlanet;
	float orbitAngle;
	int counter;
	bool isDead;
	Core *core;
	float fuel;
	int crewSize;
	ShipInterface shipinterface;
	Minimap minimap;
	std::vector<Particle> particles;
	float space;
	bool coreConnected;
public:
	float getX();
	float getY();
	void render(float xOffset, float yOffset);
	void update();
	void setPmanager(Planetmanager*p);
	bool Collision(Planet p);
	void setCore(Core *c);
	Spaceship();
	~Spaceship();
};

