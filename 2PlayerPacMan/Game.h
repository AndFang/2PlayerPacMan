#ifndef Game_h
#define Game_h

#include "Players.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	/*
	ALLEGRO_BITMAP* p1, * p2;
	ALLEGRO_BITMAP* g1, * g2, * g3;
	std::vector< ALLEGRO_BITMAP*> image;
	*/

	int curFrame1 = 0;
	int frameCount1 = 0;
	int curFrame2 = 0;
	int frameCount2 = 0;
	const int frameDelay = 10;

	Pacman p1;
	Ghost p2;
	Ghost g1, g2, g3;
};

#endif  /* Game_h */