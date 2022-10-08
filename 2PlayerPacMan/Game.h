#ifndef Game_h
#define Game_h

#include "Players.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	void start();
	void pickP1();
	void pickP2();
	void maze();

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_SAMPLE* music = NULL;

	const int frameDelay = 10;

	Pacman f, m;
	Ghost b, g, r, y;

	Pacman p1;
	Ghost p2;
	Ghost g1, g2, g3;
};

#endif  /* Game_h */