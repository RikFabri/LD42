#include "Button.h"


template<class T>
Button<T>::Button(ALLEGRO_BITMAP * texture, int x, int y, int width, int height, void(*func)(T t))
{
	this->texture = texture;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->onclick = func;
}

template<class T>
Button<T>::Button()
{
}

template<class T>
Button<T>::~Button()
{
}
