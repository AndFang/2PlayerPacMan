#include "Game.h"

Game::Game()
{
	al_init();

	display = al_create_display(1270, 809);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(1);
	music = al_load_sample("Assets/music.wav");
	assert(music != NULL);

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	al_init_image_addon();

	f = Pacman("Female");
	m = Pacman("Male");
	b = Ghost("DinoB");;
	g = Ghost("DinoG");
	r = Ghost("DinoR");
	y = Ghost("DinoY");
}

Game::~Game()
{
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_audio();
	al_destroy_timer(timer);
	// DESTROY BITMAPS
	al_destroy_sample(music);
}

void Game::run()
{
	al_play_sample(music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
	start();
	pickP1();
	pickP2();
	maze();
	
}

void Game::start()
{
	bool running = true;
	ALLEGRO_BITMAP* background = al_load_bitmap("Assets/background.jpg");
	ALLEGRO_BITMAP* text = al_load_bitmap("Assets/Start/title.png");
	ALLEGRO_BITMAP* enter = al_load_bitmap("Assets/Start/enter.png");

	int width = al_get_display_width(display);
	int runy = 665;

	f.SetDir(1);
	f.SetX(-84);
	f.SetY(runy);
	m.SetDir(1);
	m.SetX(-184);
	m.SetY(runy);
	b.SetDir(1);
	b.SetX(-284);
	b.SetY(runy + 12);
	g.SetDir(1);
	g.SetX(-384);
	g.SetY(runy + 12);
	r.SetDir(1);
	r.SetX(-484);
	r.SetY(runy + 12);
	y.SetDir(1);
	y.SetX(-584);
	y.SetY(runy + 12);

	std::vector<ALLEGRO_BITMAP*> fImage = f.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> mImage = m.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> bImage = b.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> gImage = g.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> rImage = r.GetAnnimation(2);
	std::vector<ALLEGRO_BITMAP*> yImage = y.GetAnnimation(2);

	int fFrameCount = 0;
	int fCurFrame = 0;
	int mFrameCount = 0;
	int mCurFrame = 1;
	int bFrameCount = 0;
	int bCurFrame = 0;
	int gFrameCount = 0;
	int gCurFrame = 1;
	int rFrameCount = 0;
	int rCurFrame = 2;
	int yFrameCount = 0;
	int yCurFrame = 3;

	al_start_timer(timer);
	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_ENTER))
			running = false;

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1270, 809, 0);
			al_draw_bitmap(text, 277, 150, 0);
			al_draw_scaled_bitmap(enter, 0, 0, al_get_bitmap_width(enter), al_get_bitmap_height(enter), 403, 250, 463, 19, 0);

			if (++fFrameCount >= frameDelay)
			{
				if (++fCurFrame >= fImage.size())
					fCurFrame = 0;
				fFrameCount = 0;
			}
			if (++mFrameCount >= frameDelay)
			{
				if (++mCurFrame >= mImage.size())
					mCurFrame = 0;
				mFrameCount = 0;
			}
			if (++bFrameCount >= frameDelay)
			{
				if (++bCurFrame >= bImage.size())
					bCurFrame = 0;
				bFrameCount = 0;
			}
			if (++gFrameCount >= frameDelay)
			{
				if (++gCurFrame >= gImage.size())
					gCurFrame = 0;
				gFrameCount = 0;
			}
			if (++rFrameCount >= frameDelay)
			{
				if (++rCurFrame >= rImage.size())
					rCurFrame = 0;
				rFrameCount = 0;
			}
			if (++yFrameCount >= frameDelay)
			{
				if (++yCurFrame >= yImage.size())
					yCurFrame = 0;
				yFrameCount = 0;
			}

			al_draw_scaled_bitmap(fImage[fCurFrame], 0, 0, 24, 24, f.GetX(), f.GetY(), 84, 84, 0);
			al_draw_scaled_bitmap(mImage[mCurFrame], 0, 0, 24, 24, m.GetX(), m.GetY(), 84, 84, 0);
			al_draw_scaled_bitmap(bImage[bCurFrame], 0, 0, 24, 24, b.GetX(), b.GetY(), 84, 84, 0);
			al_draw_scaled_bitmap(gImage[gCurFrame], 0, 0, 24, 24, g.GetX(), g.GetY(), 84, 84, 0);
			al_draw_scaled_bitmap(rImage[rCurFrame], 0, 0, 24, 24, r.GetX(), r.GetY(), 84, 84, 0);
			al_draw_scaled_bitmap(yImage[yCurFrame], 0, 0, 24, 24, y.GetX(), y.GetY(), 84, 84, 0);

			int speed = 4;
			f.SetX(f.GetX() + speed);
			m.SetX(m.GetX() + speed);
			b.SetX(b.GetX() + speed);
			g.SetX(g.GetX() + speed);
			r.SetX(r.GetX() + speed);
			y.SetX(y.GetX() + speed);

			if (f.GetX() > width)
				f.SetX(-84);
			if (m.GetX() > width)
				m.SetX(-84);
			if (b.GetX() > width)
				b.SetX(-84);
			if (g.GetX() > width)
				g.SetX(-84);
			if (r.GetX() > width)
				r.SetX(-84);
			if (y.GetX() > width)
				y.SetX(-84);

			al_flip_display();
		}
	}
}

void Game::pickP1()
{
	bool running = true;
	int x = 0;
	int y = 0;

	ALLEGRO_BITMAP* background = al_load_bitmap("Assets/background.jpg");
	ALLEGRO_BITMAP* text = al_load_bitmap("Assets/Start/p1.png");
	ALLEGRO_BITMAP* b1 = al_load_bitmap("Assets/Start/box.png");
	ALLEGRO_BITMAP* b2 = al_load_bitmap("Assets/Start/box.png");

	int standy = 250;
	f.SetDir(1);
	f.SetX(149);
	f.SetY(standy);
	m.SetDir(1);
	m.SetX(869);
	m.SetY(standy);

	std::vector<ALLEGRO_BITMAP*> fImage = f.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> mImage = m.GetAnnimation(3);

	int frameCount = 0;
	int curFrame = 0;

	al_start_timer(timer);
	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			x = event.mouse.x;
			y = event.mouse.y;
		}

		if (115 <= x && x <= 435 && 245 <= y && y <= 565)
		{
			p1 = f;
			running = false;
		}
		if (835 <= x && x <= 1155 && 245 <= y && y <= 565)
		{
			p1 = m;
			running = false;
		}

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1270, 809, 0);
			al_draw_scaled_bitmap(text, 0, 0, al_get_bitmap_width(text), al_get_bitmap_height(text), 204, 50, 862, 38, 0);
			al_draw_bitmap(b1, 115, 245, 0);
			al_draw_bitmap(b2, 835, 245, 0);

			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= fImage.size())
					curFrame = 0;
				frameCount = 0;
			}

			al_draw_scaled_bitmap(fImage[curFrame], 0, 0, 24, 24, f.GetX(), f.GetY(), 252, 252, 0);
			al_draw_scaled_bitmap(mImage[curFrame], 0, 0, 24, 24, m.GetX(), m.GetY(), 252, 252, 0);

			al_flip_display();
		}
	}
}

void Game::pickP2()
{
	bool running = true;
	int curx = 0;
	int cury = 0;

	ALLEGRO_BITMAP* background = al_load_bitmap("Assets/background.jpg");
	ALLEGRO_BITMAP* text = al_load_bitmap("Assets/Start/p2.png");
	ALLEGRO_BITMAP* b1 = al_load_bitmap("Assets/Start/box.png");
	ALLEGRO_BITMAP* b2 = al_load_bitmap("Assets/Start/box.png");
	ALLEGRO_BITMAP* b3 = al_load_bitmap("Assets/Start/box.png");
	ALLEGRO_BITMAP* b4 = al_load_bitmap("Assets/Start/box.png");

	int standy = 320;
	b.SetDir(1);
	b.SetX(101);
	b.SetY(standy);
	g.SetDir(1);
	g.SetX(381);
	g.SetY(standy);
	r.SetDir(1);
	r.SetX(661);
	r.SetY(standy);
	y.SetDir(1);
	y.SetX(941);
	y.SetY(standy);

	std::vector<ALLEGRO_BITMAP*> bImage = b.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> gImage = g.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> rImage = r.GetAnnimation(3);
	std::vector<ALLEGRO_BITMAP*> yImage = y.GetAnnimation(3);

	int frameCount = 0;
	int curFrame = 0;

	al_start_timer(timer);
	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			curx = event.mouse.x;
			cury = event.mouse.y;
		}

		if (75 <= curx && curx <= 315 && 285 <= cury && cury <= 525)
		{
			p2 = b;
			g1 = g;
			g2 = r;
			g3 = y;
			running = false;
		}
		if (335 <= curx && curx <= 575 && 285 <= cury && cury <= 525)
		{
			p2 = g;
			g1 = b;
			g2 = r;
			g3 = y;
			running = false;
		}
		if (635 <= curx && curx <= 875 && 285 <= cury && cury <= 525)
		{
			p2 = r;
			g1 = b;
			g2 = g;
			g3 = y;
			running = false;
		}
		if (915 <= curx && curx <= 1155 && 285 <= cury && cury <= 525)
		{
			p2 = y;
			g1 = b;
			g2 = g;
			g3 = r;
			running = false;
		}

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1270, 809, 0);
			al_draw_scaled_bitmap(text, 0, 0, al_get_bitmap_width(text), al_get_bitmap_height(text), 194, 50, 883, 38, 0);
			al_draw_scaled_bitmap(b1, 0, 0, al_get_bitmap_width(b1), al_get_bitmap_height(b1), 75, 285, 240, 240, 0);
			al_draw_scaled_bitmap(b2, 0, 0, al_get_bitmap_width(b2), al_get_bitmap_height(b2), 355, 285, 240, 240, 0);
			al_draw_scaled_bitmap(b3, 0, 0, al_get_bitmap_width(b3), al_get_bitmap_height(b3), 635, 285, 240, 240, 0);
			al_draw_scaled_bitmap(b4, 0, 0, al_get_bitmap_width(b4), al_get_bitmap_height(b4), 915, 285, 240, 240, 0);

			if (++frameCount >= frameDelay)
			{
				if (++curFrame >= bImage.size())
					curFrame = 0;
				frameCount = 0;
			}

			al_draw_scaled_bitmap(bImage[curFrame], 0, 0, 24, 24, b.GetX(), b.GetY(), 189, 189, 0);
			al_draw_scaled_bitmap(gImage[curFrame], 0, 0, 24, 24, g.GetX(), g.GetY(), 189, 189, 0);
			al_draw_scaled_bitmap(rImage[curFrame], 0, 0, 24, 24, r.GetX(), r.GetY(), 189, 189, 0);
			al_draw_scaled_bitmap(yImage[curFrame], 0, 0, 24, 24, y.GetX(), y.GetY(), 189, 189, 0);

			al_flip_display();
		}
	}


}

void Game::maze()
{
	bool running = true;

	ALLEGRO_BITMAP* background = al_load_bitmap("Assets/maze.png");

	p1.SetDir(1);
	p1.SetX(30);
	p1.SetY(40);
	p2.SetDir(1);
	p2.SetX(1000);
	p2.SetY(600);
	g1.SetDir(1);
	g1.SetX(661);
	g1.SetY(600);
	g2.SetDir(1);
	g2.SetX(941);
	g2.SetY(600);
	g3.SetDir(1);
	g3.SetX(941);
	g3.SetY(600);

	std::vector<ALLEGRO_BITMAP*> p1Image = p1.GetAnnimation(p1.GetState());
	std::vector<ALLEGRO_BITMAP*> p2Image = p2.GetAnnimation(p2.GetState());
	std::vector<ALLEGRO_BITMAP*> g1Image = g1.GetAnnimation(p1.GetState());
	std::vector<ALLEGRO_BITMAP*> g2Image = g2.GetAnnimation(p2.GetState());
	std::vector<ALLEGRO_BITMAP*> g3Image = g3.GetAnnimation(p2.GetState());

	int p1CurFrame = 0;
	int p1FrameCount = 0;
	int p2CurFrame = 0;
	int p2FrameCount = 0;

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
			std::exit(0);

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
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
		{
			p1.SetY(p1.GetY() + p1.GetSpeed());
			curState1 = 1;
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
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			p2.SetY(p2.GetY() + p2.GetSpeed());
			curState2 = 1;
		}
		else
			curState2 = 3;

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1270, 809, 0);

			if (prevDir1 != curDir1 || prevState1 != curState1)
			{
				p1.SetState(curState1);
				p1.SetDir(curDir1);

				p1Image = p1.GetAnnimation(curState1);
				p1FrameCount = frameDelay;
				p1CurFrame = p1Image.size();
			}
			if (++p1FrameCount >= frameDelay)
			{
				if (++p1CurFrame >= p1Image.size())
					p1CurFrame = 0;
				p1FrameCount = 0;
			}


			if (prevDir2 != curDir2 || prevState2 != curState2)
			{
				p2.SetState(curState2);
				p2.SetDir(curDir2);

				p2Image = p2.GetAnnimation(curState2);
				p2FrameCount = frameDelay;
				p2CurFrame = p2Image.size();
			}
			if (++p2FrameCount >= frameDelay)
			{
				if (++p2CurFrame >= p2Image.size())
					p2CurFrame = 0;
				p2FrameCount = 0;
			}

			al_draw_scaled_bitmap(p1Image[p1CurFrame], 0, 0, 24, 24, p1.GetX(), p1.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(p2Image[p2CurFrame], 0, 0, 24, 24, p2.GetX(), p2.GetY(), 48, 48, 0);

			al_flip_display();
			al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
		}
	}
}