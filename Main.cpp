#include "Game.h"
#include "allegro5/allegro_native_dialog.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "Menu.h"

Game *game;
Menu *menu;
bool menuActive = true;
int state = 0;


int main(int argc, char **argv) {
	al_init();
	al_install_audio();
	al_init_acodec_addon();
	al_init_image_addon();
	al_init_native_dialog_addon();
	al_install_keyboard();
	al_install_mouse();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	al_reserve_samples(2);
	ALLEGRO_SAMPLE *song = al_load_sample("sound/music.wav");
	ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	al_play_sample_instance(songInstance);

	restart:

	srand(time(NULL));

	game = new Game();
	menu = new Menu();
	menu->init(&menuActive, &state);
	
	al_set_display_icon(al_get_current_display(), al_load_bitmap("Images/Game-icon.png"));

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
	ALLEGRO_EVENT_QUEUE *EQ = al_create_event_queue();
	al_register_event_source(EQ, al_get_timer_event_source(timer));
	al_register_event_source(EQ, al_get_display_event_source(al_get_current_display()));
	al_start_timer(timer);



	ALLEGRO_EVENT_QUEUE *REQ = al_create_event_queue();
	al_register_event_source(REQ, al_get_keyboard_event_source());


	while (true) {
		ALLEGRO_EVENT E;
		al_wait_for_event(EQ, &E);
		if (E.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		al_get_next_event(REQ, &E);
		if (E.keyboard.keycode == ALLEGRO_KEY_R) {
			game->~Game();
			goto restart;
		}
		if (menuActive) {
			menu->render();
			menu->update();
		}
		else {
			game->update();
			game->render();
		}
	}
	return 0;
}