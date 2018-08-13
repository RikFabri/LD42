#pragma once
#include "allegro5/allegro.h"
#include <random>
#include <string>
#include "allegro5/allegro_native_dialog.h"
#include "Core.h"

class Planet
{
private:
	ALLEGRO_BITMAP *humanMark;
	ALLEGRO_BITMAP *texture;
	float x, y;
	int width, height;
	Core *core;
	bool isDead;
	int humanCount;
	int ptype;
	int oil;
	int counter;
public:
	int getOil();
	void setOil(int o);
	void setHumanCount(int c);
	int getHumanCount();
	int getWidth();
	int getHeight();
	int getType();
	float getX();
	float getY();
	void render(float xOffset, float yOffset);
	void update();
	void setCore(Core *c);
	Planet();
	~Planet();
};

