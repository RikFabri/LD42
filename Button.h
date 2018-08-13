#pragma once
#include "allegro5/allegro.h"

template<class T>
class Button
{
public:
	Button(ALLEGRO_BITMAP *texture, int x, int y, int width, int height, void(*func)(T t));
	int x, y;
	int width, height;
	ALLEGRO_BITMAP *texture;
	void(*onclick)(T t);
	Button();
	~Button();
};
