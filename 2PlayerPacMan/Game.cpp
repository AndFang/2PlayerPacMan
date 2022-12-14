#include "Game.h"

Game::Game() : _pts(0)
{
	al_init();

	display = al_create_display(1280, 816);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_install_keyboard();
	al_install_mouse();
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	al_reserve_samples(4);
	music = al_load_sample("Assets/Sounds/music.wav");
	chase = al_load_sample("Assets/Sounds/chase.wav");
	countdown = al_load_sample("Assets/Sounds/countdown.wav");
	death = al_load_sample("Assets/Sounds/death.wav");
	end = al_load_sample("Assets/Sounds/end.wav");
	thump = al_load_sample("Assets/Sounds/thump.wav");
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

	_walls.push_back({ 95,110,290,255 });
	_walls.push_back({ 95,350,290,495 });
	_walls.push_back({ 365,110,530,255 });
	_walls.push_back({ 365,350,530,705 });
	_walls.push_back({ 605,320,960,430 });
	_walls.push_back({ 605,525,750,705 });
	_walls.push_back({ 830,525,960,705 });
	_walls.push_back({ 1040,160,1185,500 });
	_walls.push_back({ 1040,590,1185,705 });
	_walls.push_back({ 605,110,865,225 });
	_walls.push_back({ 865,160,960,225 });
	_walls.push_back({ 95,590,290,660 });
	_walls.push_back({ 240,660,290,705 });

	_walls.push_back({ 0,0,1280,20 });
	_walls.push_back({ 945,20,1280,65 });
	_walls.push_back({ 0,20,20,816 });
	_walls.push_back({ 20,750,160,816 });
	_walls.push_back({ 160,795,1280,816 });
	_walls.push_back({ 1260,65,1280,795 });

	_coins.push_back(new Coin(40, 100));
	_coins.push_back(new Coin(40, 200));
	_coins.push_back(new Coin(40, 300));
	_coins.push_back(new Coin(40, 400));
	_coins.push_back(new Coin(40, 500));
	_coins.push_back(new Coin(40, 600));
	_coins.push_back(new Coin(40, 700));
	_coins.push_back(new Coin(140, 700));
	_coins.push_back(new Coin(200, 750));
	_coins.push_back(new Coin(300, 750));
	_coins.push_back(new Coin(400, 750));
	_coins.push_back(new Coin(500, 750));
	_coins.push_back(new Coin(600, 750));
	_coins.push_back(new Coin(700, 750));
	_coins.push_back(new Coin(800, 750));
	_coins.push_back(new Coin(900, 750));
	_coins.push_back(new Coin(1000, 750));
	_coins.push_back(new Coin(1100, 750));
	_coins.push_back(new Coin(1200, 750));
	_coins.push_back(new Coin(1200, 650));
	_coins.push_back(new Coin(1200, 550));
	_coins.push_back(new Coin(1200, 450));
	_coins.push_back(new Coin(1200, 350));
	_coins.push_back(new Coin(1200, 250));
	_coins.push_back(new Coin(1200, 150));
	_coins.push_back(new Coin(1100, 100));
	_coins.push_back(new Coin(1000, 100));
	_coins.push_back(new Coin(900, 100));
	_coins.push_back(new Coin(800, 50));
	_coins.push_back(new Coin(700, 50));
	_coins.push_back(new Coin(600, 50));
	_coins.push_back(new Coin(500, 50));
	_coins.push_back(new Coin(400, 50));
	_coins.push_back(new Coin(300, 50));
	_coins.push_back(new Coin(200, 50));
	_coins.push_back(new Coin(100, 50));

	_coins.push_back(new Coin(140, 300));
	_coins.push_back(new Coin(240, 300));
	_coins.push_back(new Coin(320, 300));
	_coins.push_back(new Coin(440, 300));
	_coins.push_back(new Coin(550, 320));

	_coins.push_back(new Coin(320, 120));
	_coins.push_back(new Coin(320, 220));
	_coins.push_back(new Coin(320, 420));
	_coins.push_back(new Coin(320, 520));
	_coins.push_back(new Coin(320, 620));

	_coins.push_back(new Coin(140, 520));
	_coins.push_back(new Coin(240, 520));

	_coins.push_back(new Coin(550, 120));
	_coins.push_back(new Coin(550, 220));
	_coins.push_back(new Coin(550, 420));
	_coins.push_back(new Coin(550, 520));
	_coins.push_back(new Coin(550, 620));
	_coins.push_back(new Coin(550, 700));

	_coins.push_back(new Coin(620, 265));
	_coins.push_back(new Coin(720, 265));
	_coins.push_back(new Coin(820, 265));
	_coins.push_back(new Coin(920, 265));

	_coins.push_back(new Coin(990, 170));
	_coins.push_back(new Coin(990, 270));
	_coins.push_back(new Coin(990, 370));
	_coins.push_back(new Coin(990, 470));
	_coins.push_back(new Coin(990, 570));
	_coins.push_back(new Coin(990, 670));

	_coins.push_back(new Coin(620, 470));
	_coins.push_back(new Coin(690, 470));
	_coins.push_back(new Coin(790, 470));
	_coins.push_back(new Coin(890, 470));

	_coins.push_back(new Coin(780, 550));
	_coins.push_back(new Coin(780, 650));
	_coins.push_back(new Coin(1100, 550));
}

Game::~Game()
{
	al_destroy_display(display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_audio();
	al_destroy_timer(timer);
	// DESTROY BITMAPS
	//al_destroy_sample(music);
	//al_destroy_sample(chase);
	//al_destroy_sample(countdown);
	//al_destroy_sample(death);
	//al_destroy_sample(end);
}

void Game::run()
{
	ALLEGRO_SAMPLE_ID* bm = new ALLEGRO_SAMPLE_ID();
	al_play_sample(music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, bm);
	start();
	pickP1();
	pickP2();

	int lives = 3;

	while (lives)
	{
		al_stop_sample(bm);

		ALLEGRO_BITMAP* background = al_load_bitmap("Assets/Game/maze.png");
		ALLEGRO_BITMAP* c1 = al_load_bitmap("Assets/Game/1.png");
		ALLEGRO_BITMAP* c2 = al_load_bitmap("Assets/Game/2.png");
		ALLEGRO_BITMAP* c3 = al_load_bitmap("Assets/Game/3.png");
		ALLEGRO_BITMAP* cs = al_load_bitmap("Assets/Game/start.png");
		ALLEGRO_BITMAP* con = al_load_bitmap("Assets/Game/continue.png");

		al_play_sample(countdown, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, bm);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(c3, 600, 400, 0);
		al_flip_display();
		al_rest(1);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(c2, 600, 400, 0);
		al_flip_display();
		al_rest(1);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(c1, 600, 400, 0);
		al_flip_display();
		al_rest(1);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(cs, 450, 400, 0);
		al_flip_display();
		al_rest(1);
		al_stop_sample(bm);

		al_play_sample(chase, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, bm);
		std::vector<ALLEGRO_BITMAP*> pos = maze(lives);
		al_stop_sample(bm);
		lives -= 1;

		al_play_sample(death, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, bm);
		std::vector<ALLEGRO_BITMAP*> p1death = p1.GetAnnimation(0);
		int i = 0;
		while (i != 4)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
			al_draw_scaled_bitmap(p1death[i], 0, 0, 24, 24, p1.GetX(), p1.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(pos[0], 0, 0, 24, 24, p2.GetX(), p2.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(pos[1], 0, 0, 24, 24, g1.GetX(), g1.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(pos[2], 0, 0, 24, 24, g2.GetX(), g2.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(pos[3], 0, 0, 24, 24, g3.GetX(), g3.GetY(), 48, 48, 0);
			al_flip_display();
			al_rest(0.5);
			i += 1;
		}
		if (lives)
		{
			al_draw_scaled_bitmap(con, 0, 0, al_get_bitmap_width(con), al_get_bitmap_height(con), 255, 420, 760, 30, 0);
			al_flip_display();

			bool space = true;
			ALLEGRO_EVENT event;
			ALLEGRO_KEYBOARD_STATE keyState;
			while (space)
			{
				al_wait_for_event(queue, &event);
				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					std::exit(0);

				al_get_keyboard_state(&keyState);
				if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
				{
					space = false;
				}
			}
		}
		al_stop_sample(bm);
	}

	al_play_sample(end, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, bm);
	ALLEGRO_BITMAP* over = al_load_bitmap("Assets/Game/over1.png");
	ALLEGRO_BITMAP* exit = al_load_bitmap("Assets/Game/exit.png");
	ALLEGRO_FONT* font36 = al_load_font("Assets/PixalFont.ttf", 36, 0);

	al_play_sample(thump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_draw_bitmap(over, 380, 200, 0);
	al_flip_display();
	al_rest(1.5);

	al_play_sample(thump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	std::string score = "Final Score: " + std::to_string(_pts);
	al_draw_text(font36, al_map_rgb(0, 0, 0), 420, 330, 0, score.c_str());
	al_flip_display();
	al_rest(1.5);

	al_play_sample(thump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_draw_scaled_bitmap(exit, 0, 0, al_get_bitmap_width(exit), al_get_bitmap_height(exit), 280, 420, 760, 30, 0);
	al_flip_display();

	bool space = true;
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE keyState;
	while (space)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
		{
			space = false;
		}
	}
	al_stop_sample(bm);
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
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
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
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
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
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
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

std::vector<ALLEGRO_BITMAP*> Game::maze(int lives)
{
	ALLEGRO_BITMAP* coin = al_load_bitmap("Assets/Game/coin.png");
	ALLEGRO_FONT* font36 = al_load_font("Assets/PixalFont.ttf", 36, 0);
	int frameCount = 0;

	bool running = true;

	ALLEGRO_BITMAP* background = al_load_bitmap("Assets/Game/maze.png");

	int pstartX = 30; // 900
	int pstartY = 40; // 200
	int gstartX = 930;
	int gstartY = 245;

	p1.SetDir(1);
	p1.SetX(pstartX);
	p1.SetY(pstartY);
	p2.SetDir(0);
	p2.SetX(gstartX);
	p2.SetY(gstartY);
	g1.SetDir(1);
	g1.SetX(gstartX + 50);
	g1.SetY(gstartY);
	g2.SetDir(0);
	g2.SetX(gstartX);
	g2.SetY(gstartY + 50);
	g3.SetDir(1);
	g3.SetX(gstartX + 50);
	g3.SetY(gstartY + 50);

	g1.SetMove(0);
	g2.SetMove(1);
	g3.SetMove(2);
	g1.SetState(1);
	g2.SetState(1);
	g3.SetState(1);

	//p2.SetSpeed(3);
	g1.SetSpeed(4);
	g2.SetSpeed(4);
	g3.SetSpeed(4);

	ALLEGRO_BITMAP* ltext = al_load_bitmap("Assets/Game/life.png");
	ALLEGRO_BITMAP* life = p1.GetAnnimation(p1.GetState())[0];
	int lifex = 10;
	int lifey = 765;

	std::vector<ALLEGRO_BITMAP*> p1Image = p1.GetAnnimation(p1.GetState());
	std::vector<ALLEGRO_BITMAP*> p2Image = p2.GetAnnimation(p2.GetState());
	std::vector<ALLEGRO_BITMAP*> g1Image = g1.GetAnnimation(g1.GetState());
	std::vector<ALLEGRO_BITMAP*> g2Image = g2.GetAnnimation(g2.GetState());
	std::vector<ALLEGRO_BITMAP*> g3Image = g3.GetAnnimation(g3.GetState());

	int p1CurFrame = 0;
	int p1FrameCount = 0;
	int p2CurFrame = 0;
	int p2FrameCount = 0;
	int g1CurFrame = 0;
	int g1FrameCount = 0;
	int g2CurFrame = 0;
	int g2FrameCount = 0;
	int g3CurFrame = 0;
	int g3FrameCount = 0;

	bool p1move = false;
	bool p2move = false;
	al_start_timer(timer);
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE keyState;
	while (running)
	{
		p1move = false;
		p2move = false;

		int prevState1 = p1.GetState();
		int curState1 = p1.GetState();
		bool prevDir1 = p1.GetDir();
		bool curDir1 = p1.GetDir();

		int prevState2 = p2.GetState();
		int curState2 = p2.GetState();
		bool prevDir2 = p2.GetDir();
		bool curDir2 = p2.GetDir();

		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		{
			p1move = true;
			p1.SetX(p1.GetX() + p1.GetSpeed());
			curDir1 = true;
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			p1move = true;
			p1.SetX(p1.GetX() - p1.GetSpeed());
			curDir1 = false;
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
		{
			p1move = true;
			p1.SetY(p1.GetY() - p1.GetSpeed());
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
		{
			p1move = true;
			p1.SetY(p1.GetY() + p1.GetSpeed());
			curState1 = 1;
		}
		else
			curState1 = 3;

		if (al_key_down(&keyState, ALLEGRO_KEY_D))
		{
			p2move = true;
			p2.SetX(p2.GetX() + p2.GetSpeed());
			curDir2 = true;
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
			p2move = true;
			p2.SetX(p2.GetX() - p2.GetSpeed());
			curDir2 = false;
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_W))
		{
			p2move = true;
			p2.SetY(p2.GetY() - p2.GetSpeed());
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			p2move = true;
			p2.SetY(p2.GetY() + p2.GetSpeed());
			curState2 = 1;
		}
		else
			curState2 = 3;

#if 0
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			ALLEGRO_MOUSE_STATE state;
			al_get_mouse_state(&state);
			std::cout << state.x << " " << state.y << std::endl;
		}
#endif

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);

			for (auto i : _coins)
			{
				if (i->GetShow() && i->Hit(p1.GetX() + 6, p1.GetY() + 9, p1.GetX() + 42, p1.GetY() + 45))
					_pts += 10;
				if (i->GetShow())
					al_draw_scaled_bitmap(coin, 0, 0, al_get_bitmap_width(coin), al_get_bitmap_height(coin), i->GetX(), i->GetY(), 30, 30, 0);
			}

			if (++frameCount >= frameDelay)
			{
				for (auto i : _coins)
					i->DecreaseTimeout();
				frameCount = 0;
			}

			if (ghostCollision(p1, p2) || ghostCollision(p1, g1) || ghostCollision(p1, g2) || ghostCollision(p1, g3))
			{
				running = false;
			}

			if (prevDir1 != curDir1 || prevState1 != curState1)
			{
				p1.SetState(curState1);
				p1.SetDir(curDir1);

				p1Image = p1.GetAnnimation(curState1);
				p1FrameCount = gameDelay;
				p1CurFrame = p1Image.size();
			}
			if (++p1FrameCount >= gameDelay)
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
				p2FrameCount = gameDelay;
				p2CurFrame = p2Image.size();
			}
			if (++p2FrameCount >= gameDelay)
			{
				if (++p2CurFrame >= p2Image.size())
					p2CurFrame = 0;
				p2FrameCount = 0;
			}

			if (p1move)
				wallCollision(p1);
			if (p2move)
				wallCollision(p2);

			al_draw_scaled_bitmap(p1Image[p1CurFrame], 0, 0, 24, 24, p1.GetX(), p1.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(p2Image[p2CurFrame], 0, 0, 24, 24, p2.GetX(), p2.GetY(), 48, 48, 0);

			/*
			//ALLEGRO_COLOR pos = al_get_pixel(background, p1.GetX() + 6, p1.GetY() + 12);
			//std::cout << pos.r << " " << pos.g << " " << pos.b << " " << p1.GetX() << " " << p1.GetY() << std::endl;
			ALLEGRO_COLOR red;
			red.r = 1;
			red.g = 1;
			red.b = 1;
			for (int i = 0; i < 1; i++)
				for (int j = 0; j < 1; j++)
				{
					//al_draw_pixel(i, j, pos);
					al_draw_pixel(p1.GetX() + 6, p1.GetY() + 12, red);
					al_draw_pixel(p1.GetX() + 30, p1.GetY() + 12, red);
					al_draw_pixel(p1.GetX() + 6, p1.GetY() + 36, red);
					al_draw_pixel(p1.GetX() + 30, p1.GetY() + 36, red);
					al_draw_pixel(p2.GetX() + 6, p2.GetY() + 6, red);
					al_draw_pixel(p2.GetX() + 30, p2.GetY() + 6, red);
					al_draw_pixel(p2.GetX() + 6, p2.GetY() + 30, red);
					al_draw_pixel(p2.GetX() + 30, p2.GetY() + 30, red);
				}
			//*/

			if (++g1FrameCount >= gameDelay)
			{
				if (++g1CurFrame >= g1Image.size())
					g1CurFrame = 0;
				g1FrameCount = 0;
			}
			if (++g2FrameCount >= gameDelay)
			{
				if (++g2CurFrame >= g2Image.size())
					g2CurFrame = 0;
				g2FrameCount = 0;
			}
			if (++g3FrameCount >= gameDelay)
			{
				if (++g3CurFrame >= g3Image.size())
					g3CurFrame = 0;
				g3FrameCount = 0;
			}

			AIMove(g1);
			AIMove(g2);
			AIMove(g3);

			g1Image = g1.GetAnnimation(g1.GetState());
			g2Image = g2.GetAnnimation(g2.GetState());
			g3Image = g3.GetAnnimation(g3.GetState());

			if (wallCollision(g1))
			{
				g1.SetMove((int)(((double)rand() / (RAND_MAX)) * 4));
				
			}
			if (wallCollision(g2))
			{
				g2.SetMove((int)(((double)rand() / (RAND_MAX)) * 4));
				
			}
			if (wallCollision(g3))
			{
				g3.SetMove((int)(((double)rand() / (RAND_MAX)) * 4));
				
			}

			

			al_draw_scaled_bitmap(g1Image[g1CurFrame], 0, 0, 24, 24, g1.GetX(), g1.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(g2Image[g2CurFrame], 0, 0, 24, 24, g2.GetX(), g2.GetY(), 48, 48, 0);
			al_draw_scaled_bitmap(g3Image[g3CurFrame], 0, 0, 24, 24, g3.GetX(), g3.GetY(), 48, 48, 0);

			al_draw_scaled_bitmap(ltext, 0, 0, 400, 63, lifex + 10, lifey - 10, 50, 13, 0);
			for (int i = 0; i < lives; i++)
			{
				al_draw_scaled_bitmap(life, 0, 0, 24, 24, lifex + i * 40, lifey, 36, 36, 0);
			}

			std::string score = "Score: " + std::to_string(_pts);
			al_draw_text(font36, al_map_rgb(0, 0, 0), 950, 20, 0, score.c_str());

			al_flip_display();
		}
	}

	std::vector<ALLEGRO_BITMAP*> pos;
	pos.push_back(p2Image[p2CurFrame]);
	pos.push_back(g1Image[g1CurFrame]);
	pos.push_back(g2Image[g2CurFrame]);
	pos.push_back(g3Image[g3CurFrame]);

	return pos;
}

bool Game::wallCollision(Player& p)
{
	int l = p.GetX() + 6;
	int r = l + 36;
	int t = p.GetY() + 9;
	int b = t + 36;

	bool hit = false;

	for (auto w : _walls)
	{
		if (w[0] <= l && l <= w[2] && w[1] <= t && t <= w[3])
		{
			p.SetX(p.GetX() + p.GetSpeed());
			p.SetY(p.GetY() + p.GetSpeed());
			hit = true;
		}
		if (w[0] <= r && r <= w[2] && w[1] <= t && t <= w[3])
		{
			p.SetX(p.GetX() - p.GetSpeed());
			p.SetY(p.GetY() + p.GetSpeed());
			hit = true;
		}
		if (w[0] <= l && l <= w[2] && w[1] <= b && b <= w[3])
		{
			p.SetX(p.GetX() + p.GetSpeed());
			p.SetY(p.GetY() - p.GetSpeed());
			hit = true;
		}
		if (w[0] <= r && r <= w[2] && w[1] <= b && b <= w[3])
		{
			p.SetX(p.GetX() - p.GetSpeed());
			p.SetY(p.GetY() - p.GetSpeed());
			hit = true;
		}
	}

	return hit;

#if 0
	ALLEGRO_COLOR lt = al_get_pixel(bg, l, t);
	ALLEGRO_COLOR rt = al_get_pixel(bg, r, t);
	ALLEGRO_COLOR lb = al_get_pixel(bg, l, b);
	ALLEGRO_COLOR rb = al_get_pixel(bg, r, b);

	float wall = 0.839216;

	if (fabs(lt.r - wall) < 0.01)
	{
		p.SetX(p.GetX() + p.GetSpeed());
		p.SetY(p.GetY() + p.GetSpeed());
	}
	if (fabs(rt.r - wall) < 0.01)
	{
		p.SetX(p.GetX() - p.GetSpeed());
		p.SetY(p.GetY() + p.GetSpeed());
	}
	if (fabs(lb.r - wall) < 0.01)
	{
		p.SetX(p.GetX() + p.GetSpeed());
		p.SetY(p.GetY() - p.GetSpeed());
	}
	if (fabs(rb.r - wall) < 0.01)
	{
		p.SetX(p.GetX() - p.GetSpeed());
		p.SetY(p.GetY() - p.GetSpeed());
	}
#endif
}

bool Game::ghostCollision(Player& p, Player& g)
{
	int pl = p.GetX() + 6;
	int pt = p.GetY() + 9;
	int pr = pl + 36;
	int pb = pt + 36;

	int gl = g.GetX() + 6;
	int gt = g.GetY() + 9;
	int gr = gl + 36;
	int gb = gt + 36;

	if (pl > gr || gl > pr)
		return false;

	if (pb < gt || gb < pt)
		return false;

	return true;
}

void Game::AIMove(Player& p)
{
	double change = ((double)rand() / (RAND_MAX));
	if (change < 0.02)
		p.SetMove((int)(((double)rand() / (RAND_MAX)) * 4));

	switch (p.GetMove())
	{
		case 0:
			p.SetX(p.GetX() + p.GetSpeed());
			p.SetDir(true);
			return;
		case 1:
			p.SetX(p.GetX() - p.GetSpeed());
			p.SetDir(false);
			return;
		case 2:
			p.SetY(p.GetY() - p.GetSpeed());
			return;
		case 3:
			p.SetY(p.GetY() + p.GetSpeed());
			return;
	}

	p.SetState(1);
}

#if 0
const float FPS = 60;

Game::Game() : _width(1280), _height(816), _finish(false), _display(NULL), _timer(NULL), _queue(NULL)
{
	Init();
}

Game::~Game()
{
	Shutdown();
}

void Game::Run()
{
	while (!_finish)
	{
		_curEvent = WaitForEvent();

		if (_curEvent == EV_NULL)
		{
			continue;
		}
		if (_curEvent == EV_CLOSE)
		{
			break;
		}

		RenderStart();
		Notify();
		if (_curEvent == EV_TIMER)
		{
			RenderEnd();
		}
	}
}

void Game::CursorPosition(int& cx, int& cy) const
{
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	cx = state.x;
	cy = state.y;
}

void Game::DrawImage(ALLEGRO_BITMAP* image, int x, int y)
{
	al_draw_bitmap(image, x, y, 0);
}

void Game::DrawImageScaled(ALLEGRO_BITMAP* image, int x, int y, int sx, int sy)
{
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, sx, sy, 0);
}

void Game::Init()
{
	if (!al_init())
	{
		cout << "Failed to initialize allegro\n";
		exit(-1);
	}

	if (!al_install_keyboard())
	{
		cout << "Failed to initialize the keyboard\n";
		exit(-1);
	}

	if (!al_install_mouse())
	{
		cout << "Failed to initialize the mouse\n";
		exit(-1);
	}

	if (!al_install_audio())
	{
		cout << "Failed to initialize the audio\n";
		exit(-1);
	}
	if (!al_init_acodec_addon())
	{
		cout << "Failed to initialize the samples\n";
		exit(-1);
	}

	_bm = new ALLEGRO_SAMPLE_ID();
	if (!_bm)
	{
		cout << "Failed to initialize the sample mixer\n";
		exit(-1);
	}

	_timer = al_create_timer(1.0 / FPS);
	if (!_timer) {
		cout << "Failed to create timer\n";
		exit(-1);
	}

	_display = al_create_display(_width, _height);
	if (!_display)
	{
		cout << "Failed to create display\n";
		Shutdown();
		exit(-1);
	}
	al_set_target_bitmap(al_get_backbuffer(_display)); // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	_queue = al_create_event_queue();
	if (!_queue) {
		cout << "Failed to create queue\n";
		Shutdown();
		exit(-1);
	}
	
	al_register_event_source(_queue, al_get_display_event_source(_display));
	al_register_event_source(_queue, al_get_timer_event_source(_timer));
	al_register_event_source(_queue, al_get_keyboard_event_source());
	al_register_event_source(_queue, al_get_mouse_event_source());

	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_flip_display();
	al_start_timer(_timer);

	al_init_image_addon();
}

void Game::Shutdown()
{
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_audio();

	if (_timer)
	{
		al_destroy_timer(_timer);
		_timer = NULL;
	}

	if (_display)
	{
		al_destroy_display(_display);
		_display = NULL;
	}
	
	if (_queue)
	{
		al_destroy_event_queue(_queue);
		_queue = NULL;
	}

	delete _bm;
}

EventType Game::WaitForEvent()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(_queue, &ev);

	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	{
		return EV_CLOSE;
	}

	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
	{
		return EV_MOUSE_UP;
	}

	if (ev.type == ALLEGRO_EVENT_TIMER) {
		return EV_TIMER;
	}
		
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode)
		{
			case ALLEGRO_KEY_ENTER:
				return EV_ENTER;
			case ALLEGRO_KEY_SPACE:
				return EV_SPACE;
		}
	}

	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);
	if (al_key_down(&keyState, ALLEGRO_KEY_UP))
		return EV_UP;
	if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
		return EV_DOWN;
	if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		return EV_LEFT;
	if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		return EV_RIGHT;
	if (al_key_down(&keyState, ALLEGRO_KEY_A))
		return EV_A;
	if (al_key_down(&keyState, ALLEGRO_KEY_S))
		return EV_S;
	if (al_key_down(&keyState, ALLEGRO_KEY_D))
		return EV_D;
	if (al_key_down(&keyState, ALLEGRO_KEY_W))
		return EV_W;


	return EV_NULL;
}

void Game::RenderStart()
{
	al_clear_to_color(al_map_rgb(255, 255, 255));
}

void Game::RenderEnd()
{
	al_flip_display();
}

void Game::run()
{
	ALLEGRO_SAMPLE_ID* bm = new ALLEGRO_SAMPLE_ID();
	al_play_sample(_music, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, bm);

	int lives = 3;

	while (lives)
	{
		al_stop_sample(bm);

		ALLEGRO_BITMAP* background = al_load_bitmap("Assets/Game/maze.png");
		ALLEGRO_BITMAP* c1 = al_load_bitmap("Assets/Game/1.png");
		ALLEGRO_BITMAP* c2 = al_load_bitmap("Assets/Game/2.png");
		ALLEGRO_BITMAP* c3 = al_load_bitmap("Assets/Game/3.png");
		ALLEGRO_BITMAP* cs = al_load_bitmap("Assets/Game/start.png");
		ALLEGRO_BITMAP* con = al_load_bitmap("Assets/Game/continue.png");
		
		al_play_sample(_countdown, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, bm);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(c3, 600, 400, 0);
		al_flip_display();
		al_rest(1);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(c2, 600, 400, 0);
		al_flip_display();
		al_rest(1);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(c1, 600, 400, 0);
		al_flip_display();
		al_rest(1);
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
		al_draw_bitmap(cs, 450, 400, 0);
		al_flip_display();
		al_rest(1);
		al_stop_sample(bm);
		
		al_play_sample(chase, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, bm);
		std::vector<ALLEGRO_BITMAP*> pos = maze(lives);
		al_stop_sample(bm);
		lives -= 1;

		al_play_sample(death, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, bm);
		std::vector<ALLEGRO_BITMAP*> p1death = p1.GetAnnimation(0);
		int i = 0;
		while (i != 4)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
			al_draw_scaled_bitmap(p1death[i], 0, 0, 24, 24, p1.GetX(), p1.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(pos[0], 0, 0, 24, 24, p2.GetX(), p2.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(pos[1], 0, 0, 24, 24, g1.GetX(), g1.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(pos[2], 0, 0, 24, 24, g2.GetX(), g2.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(pos[3], 0, 0, 24, 24, g3.GetX(), g3.GetY(), 36, 36, 0);
			al_flip_display();
			al_rest(0.5);
			i += 1;
		}
		if (lives)
		{
			al_draw_scaled_bitmap(con, 0, 0, al_get_bitmap_width(con), al_get_bitmap_height(con), 255, 420, 760, 30, 0);
			al_flip_display();

			bool space = true;
			ALLEGRO_EVENT event;
			ALLEGRO_KEYBOARD_STATE keyState;
			while (space)
			{
				al_wait_for_event(queue, &event);
				if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					std::exit(0);
				
				al_get_keyboard_state(&keyState);
				if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
				{
					space = false;
				}
			}
		}
		al_stop_sample(bm);
	}

	al_play_sample(end, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, bm);
	ALLEGRO_BITMAP* over = al_load_bitmap("Assets/Game/over1.png");
	ALLEGRO_BITMAP* exit = al_load_bitmap("Assets/Game/exit.png");

	al_play_sample(thump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_draw_bitmap(over, 380, 200, 0);
	al_flip_display();
	al_rest(1.5);

	al_play_sample(thump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	al_draw_scaled_bitmap(exit, 0, 0, al_get_bitmap_width(exit), al_get_bitmap_height(exit), 280, 420, 760, 30, 0);
	al_flip_display();
	bool space = true;
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE keyState;
	while (space)
	{
		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
		{
			space = false;
		}
	}
	al_stop_sample(bm);
}

std::vector<ALLEGRO_BITMAP*> Game::maze(int lives)
{
	bool running = true;

	ALLEGRO_BITMAP* background = al_load_bitmap("Assets/Game/maze.png");

	int pstartX = 900; // 30
	int pstartY = 200; // 40
	int gstartX = 930;
	int gstartY = 245;

	p1.SetDir(1);
	p1.SetX(pstartX);
	p1.SetY(pstartY);
	p2.SetDir(0);
	p2.SetX(gstartX);
	p2.SetY(gstartY);
	g1.SetDir(1);
	g1.SetX(gstartX + 50);
	g1.SetY(gstartY);
	g2.SetDir(0);
	g2.SetX(gstartX);
	g2.SetY(gstartY + 50);
	g3.SetDir(1);
	g3.SetX(gstartX + 50);
	g3.SetY(gstartY + 50);

	ALLEGRO_BITMAP* ltext = al_load_bitmap("Assets/Game/life.png");
	ALLEGRO_BITMAP* life = p1.GetAnnimation(p1.GetState())[0];
	int lifex = 10;
	int lifey = 765;

	std::vector<ALLEGRO_BITMAP*> p1Image = p1.GetAnnimation(p1.GetState());
	std::vector<ALLEGRO_BITMAP*> p2Image = p2.GetAnnimation(p2.GetState());
	std::vector<ALLEGRO_BITMAP*> g1Image = g1.GetAnnimation(p1.GetState());
	std::vector<ALLEGRO_BITMAP*> g2Image = g2.GetAnnimation(p2.GetState());
	std::vector<ALLEGRO_BITMAP*> g3Image = g3.GetAnnimation(p2.GetState());

	int p1CurFrame = 0;
	int p1FrameCount = 0;
	int p2CurFrame = 0;
	int p2FrameCount = 0;
	int g1CurFrame = 0;
	int g1FrameCount = 0;
	int g2CurFrame = 0;
	int g2FrameCount = 0;
	int g3CurFrame = 0;
	int g3FrameCount = 0;

	bool p1move = false;
	bool p2move = false;
	al_start_timer(timer);
	ALLEGRO_EVENT event;
	ALLEGRO_KEYBOARD_STATE keyState;
	while (running)
	{
		p1move = false;
		p2move = false;

		int prevState1 = p1.GetState();
		int curState1 = p1.GetState();
		bool prevDir1 = p1.GetDir();
		bool curDir1 = p1.GetDir();

		int prevState2 = p2.GetState();
		int curState2 = p2.GetState();
		bool prevDir2 = p2.GetDir();
		bool curDir2 = p2.GetDir();

		al_wait_for_event(queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			std::exit(0);

		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		{
			p1move = true;
			p1.SetX(p1.GetX() + p1.GetSpeed());
			curDir1 = true;
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			p1move = true;
			p1.SetX(p1.GetX() - p1.GetSpeed());
			curDir1 = false;
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
		{
			p1move = true;
			p1.SetY(p1.GetY() - p1.GetSpeed());
			curState1 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
		{
			p1move = true;
			p1.SetY(p1.GetY() + p1.GetSpeed());
			curState1 = 1;
		}
		else
			curState1 = 3;

		if (al_key_down(&keyState, ALLEGRO_KEY_D))
		{
			p2move = true;
			p2.SetX(p2.GetX() + p2.GetSpeed());
			curDir2 = true;
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_A))
		{
			p2move = true;
			p2.SetX(p2.GetX() - p2.GetSpeed());
			curDir2 = false;
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_W))
		{
			p2move = true;
			p2.SetY(p2.GetY() - p2.GetSpeed());
			curState2 = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_S))
		{
			p2move = true;
			p2.SetY(p2.GetY() + p2.GetSpeed());
			curState2 = 1;
		}
		else
			curState2 = 3;

		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), 0, 0, 1280, 816, 0);
			
			if (ghostCollision(p1, p2) || ghostCollision(p1, g1) || ghostCollision(p1, g2) || ghostCollision(p1, g3))
			{
				running = false;
			}

			if (prevDir1 != curDir1 || prevState1 != curState1)
			{
				p1.SetState(curState1);
				p1.SetDir(curDir1);

				p1Image = p1.GetAnnimation(curState1);
				p1FrameCount = GAMEDELAY;
				p1CurFrame = p1Image.size();
			}
			if (++p1FrameCount >= GAMEDELAY)
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
				p2FrameCount = GAMEDELAY;
				p2CurFrame = p2Image.size();
			}
			if (++p2FrameCount >= GAMEDELAY)
			{
				if (++p2CurFrame >= p2Image.size())
					p2CurFrame = 0;
				p2FrameCount = 0;
			}

			if (p1move)
				wallCollision(p1, background);
			if (p2move)
				wallCollision(p2, background);

			al_draw_scaled_bitmap(p1Image[p1CurFrame], 0, 0, 24, 24, p1.GetX(), p1.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(p2Image[p2CurFrame], 0, 0, 24, 24, p2.GetX(), p2.GetY(), 36, 36, 0);

			/*
			//ALLEGRO_COLOR pos = al_get_pixel(background, p1.GetX() + 6, p1.GetY() + 12);
			//std::cout << pos.r << " " << pos.g << " " << pos.b << " " << p1.GetX() << " " << p1.GetY() << std::endl;
			ALLEGRO_COLOR red;
			red.r = 1;
			red.g = 1;
			red.b = 1;

			for (int i = 0; i < 1; i++)
				for (int j = 0; j < 1; j++)
				{
					//al_draw_pixel(i, j, pos);
					al_draw_pixel(p1.GetX() + 6, p1.GetY() + 12, red);
					al_draw_pixel(p1.GetX() + 30, p1.GetY() + 12, red);
					al_draw_pixel(p1.GetX() + 6, p1.GetY() + 36, red);
					al_draw_pixel(p1.GetX() + 30, p1.GetY() + 36, red);

					al_draw_pixel(p2.GetX() + 6, p2.GetY() + 6, red);
					al_draw_pixel(p2.GetX() + 30, p2.GetY() + 6, red);
					al_draw_pixel(p2.GetX() + 6, p2.GetY() + 30, red);
					al_draw_pixel(p2.GetX() + 30, p2.GetY() + 30, red);
				}
			//*/

			if (++g1FrameCount >= GAMEDELAY)
			{
				if (++g1CurFrame >= g1Image.size())
					g1CurFrame = 0;
				g1FrameCount = 0;
			}
			if (++g2FrameCount >= GAMEDELAY)
			{
				if (++g2CurFrame >= g2Image.size())
					g2CurFrame = 0;
				g2FrameCount = 0;
			}
			if (++g3FrameCount >= GAMEDELAY)
			{
				if (++g3CurFrame >= g3Image.size())
					g3CurFrame = 0;
				g3FrameCount = 0;
			}

			wallCollision(g1, background);
			wallCollision(g2, background);
			wallCollision(g3, background);

			al_draw_scaled_bitmap(g1Image[g1CurFrame], 0, 0, 24, 24, g1.GetX(), g1.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(g2Image[g2CurFrame], 0, 0, 24, 24, g2.GetX(), g2.GetY(), 36, 36, 0);
			al_draw_scaled_bitmap(g3Image[g3CurFrame], 0, 0, 24, 24, g3.GetX(), g3.GetY(), 36, 36, 0);

			al_draw_scaled_bitmap(ltext, 0, 0, 400, 63, lifex + 10, lifey - 10, 50, 13, 0);
			for (int i = 0; i < lives; i++)
			{
				al_draw_scaled_bitmap(life, 0, 0, 24, 24, lifex + i * 40, lifey, 36, 36, 0);
			}

			al_flip_display();
		}
	}

	std::vector<ALLEGRO_BITMAP*> pos;
	pos.push_back(p2Image[p2CurFrame]);
	pos.push_back(g1Image[g1CurFrame]);
	pos.push_back(g2Image[g2CurFrame]);
	pos.push_back(g3Image[g3CurFrame]);

	return pos;
}
#endif