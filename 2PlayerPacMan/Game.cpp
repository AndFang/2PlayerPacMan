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

	p1 = Pacman("Male");
	p1.SetX(50);
	p1.SetY(50);

	p2 = Ghost("DinoR");
	p2.SetX(500);
	p2.SetY(500);
}

Game::~Game()
{
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(timer);
}

void Game::run()
{
	bool running = true;
	int width = al_get_display_width(display);
	std::vector<ALLEGRO_BITMAP*> image1 = p1.GetAnnimation(p1.GetState());
	std::vector<ALLEGRO_BITMAP*> image2 = p2.GetAnnimation(p2.GetState());

	al_start_timer(timer);
	while (running)
	{
		int prevState1 = p1.GetState();
		int curState1 = p1.GetState();
		bool prevDir1 = p1.GetDir();
		bool curDir1 = p1.GetDir();

		int prevState2 = p2.GetState();
		int curState2 = p2.GetState();
		bool prevDir2 = p2.GetDir();
		bool curDir2 = p2.GetDir();

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			// NOTHING
		}

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			/*
			x = y = 0;
			al_set_mouse_xy(display, 0, 0);
			*/
		}

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		{
			p1.SetX(p1.GetX() + p1.GetSpeed());
			curDir1 = true;
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			p1.SetX(p1.GetX() - p1.GetSpeed());
			curDir1 = false;
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
		{
			p1.SetY(p1.GetY() - p1.GetSpeed());
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
		{
			p1.SetY(p1.GetY() + p1.GetSpeed());
		}
		else
			curState1 = 3;

		if (al_key_down(&keyState, ALLEGRO_KEY_D))
		{
			p2.SetX(p2.GetX() + p2.GetSpeed());
			curDir2 = true;
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
			p2.SetX(p2.GetX() - p2.GetSpeed());
			curDir2 = false;
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_W))
		{
			p2.SetY(p2.GetY() - p2.GetSpeed());
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			p2.SetY(p2.GetY() + p2.GetSpeed());
		}
		else
			curState2 = 3;


		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			if (prevDir1 != curDir1 || prevState1 != curState1)
			{
				p1.SetState(curState1);
				p1.SetDir(curDir1);

				image1 = p1.GetAnnimation(curState1);
				frameCount1 = frameDelay;
				curFrame1 = image1.size();
			}

			if (++frameCount1 >= frameDelay)
			{
				if (++curFrame1 >= image1.size())
					curFrame1 = 0;
				frameCount1 = 0;
			}



			if (prevDir2 != curDir2 || prevState2 != curState2)
			{
				p2.SetState(curState2);
				p2.SetDir(curDir2);

				image2 = p2.GetAnnimation(curState2);
				frameCount2 = frameDelay;
				curFrame2 = image2.size();
			}

			if (++frameCount2 >= frameDelay)
			{
				if (++curFrame2 >= image2.size())
					curFrame2 = 0;
				frameCount2 = 0;
			}

			al_draw_scaled_bitmap(image1[curFrame1], 0, 0, 24, 24, p1.GetX(), p1.GetY(), 84, 84, 0);
			al_draw_scaled_bitmap(image2[curFrame2], 0, 0, 24, 24, p2.GetX(), p2.GetY(), 84, 84, 0);

			al_flip_display(); // draw the screen
			al_clear_to_color(al_map_rgba_f(1,1,1,1));

		}
	}
}