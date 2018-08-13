#pragma once
#include "Spaceship.h"

class Camera
{
private:
	int xOffset, yOffset;
public:
	void update(Spaceship *spaceship);
	float getXoffset();
	float getYoffset();
	Camera();
	~Camera();
};

