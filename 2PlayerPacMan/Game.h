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
	ALLEGRO_BITMAP* p1, * p2;
	ALLEGRO_BITMAP* g1, * g2, * g3;
	std::vector< ALLEGRO_BITMAP*> image;

	int curFrame;
	int frameCount;
	int frameDelay;
};

#endif  /* Game_h */