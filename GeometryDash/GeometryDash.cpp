#include <allegro5/allegro.h>

//constants and globals
const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;

enum MYKEYS { //enumerations just exist so we dont have to remember numbers
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main()
{
	//allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_BITMAP* bouncer = NULL;

	//player and game variables
	float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
	bool key[4] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;

	//set up allegro
	al_init();
	al_install_keyboard();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);

	//set up player (KEEPS THESE IN THE ORDER THEY ARE IF YOURE MAKING ANOTHER PLAYER)
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 0, 255));

	//set up rest of the game
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display();
	al_start_timer(timer);

	//game loop
	while (!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//TIMER SECTION//////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && bouncer_y >= 4.0) {
				bouncer_y -= 4.0;

			}

			if (key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				bouncer_y += 4.0;
			}
			if (key[KEY_LEFT] && bouncer_x >= 4.0) {
				bouncer_x -= 4.0;

			}

			if (key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				bouncer_x += 4.0;
			}

			redraw = true;

		}

		//INPUT/OUTPUT SECTION////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			}

		}


		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;

			}

		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);

			al_flip_display();

		}
	}

	//clear up memory

	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0; //kills program


}