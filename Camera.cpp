#include "Camera.h"



void Camera::update(Spaceship * spaceship)
{
	xOffset = 640 - spaceship->getX();
	yOffset = 360 - spaceship->getY();
}

float Camera::getXoffset()
{
	return xOffset;
}

float Camera::getYoffset()
{
	return yOffset;
}

Camera::Camera()
{
}


Camera::~Camera()
{
}
