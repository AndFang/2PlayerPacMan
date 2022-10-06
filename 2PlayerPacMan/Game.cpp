#include "Game.h"

Game::Game()
{
	al_init();

	display = al_create_display(1270, 809);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_init_image_addon();

	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;

	image.push_back(al_load_bitmap("Assets/Male/L/Stand/Stand0.png"));
	image.push_back(al_load_bitmap("Assets/Male/L/Stand/Stand1.png"));
	image.push_back(al_load_bitmap("Assets/Male/L/Stand/Stand2.png"));
	image.push_back(al_load_bitmap("Assets/Male/L/Stand/Stand3.png"));

	p1 = al_load_bitmap("Assets/Male/L/Stand/Stand1.png");
	p2 = al_load_bitmap("Assets/DinoR/L/Stand/Stand0.png");
	g1 = al_load_bitmap("Assets/DinoB/L/Stand/Stand0.png");
	g2 = al_load_bitmap("Assets/DinoY/L/Stand/Stand0.png");
	g3 = al_load_bitmap("Assets/DinoG/L/Stand/Stand0.png");

	assert(p1 != NULL);
	assert(p2 != NULL);
	assert(g1 != NULL);
	assert(g2 != NULL);
	assert(g3 != NULL);
}

Game::~Game()
{
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_bitmap(p1);
	al_destroy_bitmap(p2);
	al_destroy_bitmap(g1);
	al_destroy_bitmap(g2);
	al_destroy_bitmap(g3);

	for (int i = 0; i < image.size(); i++)
		al_destroy_bitmap(image[i]);
}

void Game::run()
{
	bool running = true;
	float x = 0, y = 0;
	int width = al_get_display_width(display);

	al_start_timer(timer);
	while (running)
	{

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		// mouse
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = event.mouse.x;
			y = event.mouse.y;
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			x = y = 0;
			al_set_mouse_xy(display, 0, 0);
		}

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_UP))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				x += 10;
			else
				x += 1;


		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= image.size())
					curFrame = 0;
				frameCount = 0;
			}

			al_draw_scaled_bitmap(image[curFrame], 0, 0, 24, 24, x, y, 84, 84, 0);
			
			// al_draw_bitmap(p1, x, y, 0);
			al_flip_display(); // draw the screen
			al_clear_to_color(al_map_rgba_f(1,1,1,1));

		}



		if (x > width)
			x = -al_get_bitmap_width(p1);
	}
}