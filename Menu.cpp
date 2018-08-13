#include "Menu.h"

void Menu::update()
{
	if (running) {
		ALLEGRO_EVENT E;
		al_get_next_event(EQ, &E);
		if (E.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			if (E.mouse.x > playBtn.x && E.mouse.x < playBtn.x + playBtn.width && E.mouse.y > playBtn.y && E.mouse.y < playBtn.y + playBtn.height && *state == 0) {
				playBtn.onclick(menuActive);
			}
			if (E.mouse.x > infoBtn.x && E.mouse.x < infoBtn.x + infoBtn.width && E.mouse.y > infoBtn.y && E.mouse.y < infoBtn.y + infoBtn.height && *state == 0) {
				infoBtn.onclick(state);
			}
			if (E.mouse.x > backBtn.x && E.mouse.x < backBtn.x + backBtn.width && E.mouse.y > backBtn.y && E.mouse.y < backBtn.y + backBtn.height && *state == 1) {
				backBtn.onclick(state);
			}
		}
		else {
			if (E.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}
		}
	}
}

void Menu::render()
{
	if (*state == 0) {
		al_draw_bitmap(startBG, 0, 0, 0);
		al_draw_bitmap(playBtn.texture, playBtn.x, playBtn.y, 0);
	}
	else {
		if (*state == 1) {
			al_draw_bitmap(infoBG, 0, 0, 0);
			al_draw_bitmap(backBtn.texture, backBtn.x, backBtn.y, 0);
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 100, ALLEGRO_ALIGN_CENTRE, "Arrows: steer --uses fuel--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 125, ALLEGRO_ALIGN_CENTRE, "Spacebar: release from planet orbit");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 150, ALLEGRO_ALIGN_CENTRE, "--Planets with an exclamation mark have life on them. You can pick the lifeforms up using the plus sign.--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 175, ALLEGRO_ALIGN_CENTRE, "--Your crew can be dropped on any planet using the minus sign.");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 200, ALLEGRO_ALIGN_CENTRE, "If it's a green planet each member you drop off gathers oil.--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 225, ALLEGRO_ALIGN_CENTRE, "--more members equals faster oil--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 250, ALLEGRO_ALIGN_CENTRE, "--You have a limited amount of space in the ship, find a nice balance between crew members and the amount of fuel--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 275, ALLEGRO_ALIGN_CENTRE, "--The universe is getting smaller. Get the core's fuel back to a 100 and watch out to not touch the edge");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 300, ALLEGRO_ALIGN_CENTRE, "of the universe or orbit around a planet that's about to die.--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 325, ALLEGRO_ALIGN_CENTRE, "--Touch a planet to orbit around it.--");
			al_draw_text(font, al_map_rgb(0, 242, 255), 640, 350, ALLEGRO_ALIGN_CENTRE, "--Press r to restart.--");
		}
	}
	al_flip_display();
}

void Menu::init(bool *mA, int *s)
{
	font = al_load_font("aliee13.ttf", 20, 0);
	startBG = al_load_bitmap("Images/startBG.png");
	infoBG = al_load_bitmap("Images/infoBG.png");
	menuActive = mA;
	state = s;
	running = true;
	EQ = al_create_event_queue();
	al_register_event_source(EQ, al_get_display_event_source(al_get_current_display()));
	al_register_event_source(EQ, al_get_mouse_event_source());

	playBtn = (Button<bool*>(al_load_bitmap("Images/play_btn.png"), 452, 410, 384, 151, [](bool* mA) {*mA = false; }));
	infoBtn = (Button<int*>(al_load_bitmap("Images/infoBtn.png"), 271, 573, 745, 133, [](int* s) {*s = 1; }));
	backBtn = (Button<int*>(al_load_bitmap("Images/backBtn.png"), 565, 500, 149, 71, [](int* s) {*s = 0; }));
}
