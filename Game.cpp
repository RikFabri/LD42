#include "Game.h"



void Game::update()
{
	cam.update(spaceship);
	planetmanager.update();
	spaceship->update();
	core->update();
}

void Game::render()
{
	al_clear_to_color(black);
	core->render(cam.getXoffset(), cam.getYoffset());
	planetmanager.render(cam.getXoffset(), cam.getYoffset());
	spaceship->render(cam.getXoffset(), cam.getYoffset());
	al_flip_display();
}

Game::Game()
{
	al_set_new_display_flags(ALLEGRO_RESIZABLE);
	this->display = al_create_display(1280, 720);
	al_set_window_title(display, "LD42 - The crunch");
	this->spaceship = new Spaceship();
	this->core = new Core();
	black = al_map_rgb(0, 0, 0);
	planetmanager = Planetmanager();
	planetmanager.setCore(core);
	spaceship->setPmanager(&planetmanager);
	spaceship->setCore(core);
	cam = Camera();
}


Game::~Game()
{
	al_destroy_display(display);
}
