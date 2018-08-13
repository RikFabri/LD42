#pragma once
#include "allegro5/allegro.h"
#include "Button.h"
#include <iostream>
#include <vector>
#include "MenuFunctions.h"
#include "allegro5/allegro_font.h"


class Menu
{
private:
	ALLEGRO_FONT *font;
	ALLEGRO_BITMAP * startBG;
	ALLEGRO_BITMAP * infoBG;
	MenuFunctions * mFunctions;
	ALLEGRO_EVENT_QUEUE *EQ;
	Button<bool*> playBtn;
	Button<int*> infoBtn;
	Button<int*> backBtn;
	bool running;
	bool *menuActive;
	int *state;
public:
	void init(bool *mA, int *s);
	void render();
	void update();
};

