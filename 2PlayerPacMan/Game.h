#ifndef Game_h
#define Game_h

#include "Players.h"
#include "Coin.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <iostream>

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
	std::vector<ALLEGRO_BITMAP*> maze(int lives);
	bool wallCollision(Player& p);
	bool ghostCollision(Player& p, Player& g);
	void AIMove(Player& p);

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_SAMPLE* music;
	ALLEGRO_SAMPLE* chase;
	ALLEGRO_SAMPLE* countdown;
	ALLEGRO_SAMPLE* death;
	ALLEGRO_SAMPLE* end;
	ALLEGRO_SAMPLE* thump;

	const int frameDelay = 10;
	const int gameDelay = 10;

	Pacman f, m;
	Ghost b, g, r, y;

	Pacman p1;
	Ghost p2;
	Ghost g1, g2, g3;

	std::vector<std::vector<int>> _walls;
	std::vector<Coin*> _coins;
	int _pts;
};

#if 0
#include "Observer.h"
#include "Players.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>

enum EventType
{
	EV_NULL = -1,
	EV_CLOSE = 0,
	EV_MOUSE_UP = 1,
	EV_ENTER = 2,
	EV_SPACE = 3,
	EV_UP = 4,
	EV_DOWN = 5,
	EV_LEFT = 6,
	EV_RIGHT = 7,
	EV_A = 8,
	EV_S = 9,
	EV_D = 10,
	EV_W = 11,
	EV_TIMER = 12
};

class Game : public ObserverSubject
{
public:
	Game();
	~Game();

	void Run();
	EventType CurrentEvent() { return _curEvent; }
	void CursorPosition(int& cx, int& cy) const;

	void DrawImage(ALLEGRO_BITMAP* image, int x, int y);
	void DrawImageScaled(ALLEGRO_BITMAP* image, int x, int y, int sx, int sy);
	void Done() { _finish = true; }
	int GetW() { return _width; }
	int GetH() { return _height; }
	void AudioPlay(ALLEGRO_SAMPLE* audio) { al_play_sample(audio, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, _bm); }
	void AudioStop() { al_stop_sample(_bm); }
private:
	void Init();
	void Shutdown();
	EventType WaitForEvent();
	void RenderStart();
	void RenderEnd();

	int _width;
	int _height;
	bool _finish;
	EventType _curEvent;

	ALLEGRO_DISPLAY* _display;
	ALLEGRO_EVENT_QUEUE* _queue;
	ALLEGRO_TIMER* _timer;
	ALLEGRO_SAMPLE_ID* _bm;

	void Countdown();

	std::vector<ALLEGRO_BITMAP*> maze(int lives);
};
#endif 

#endif  /* Game_h */