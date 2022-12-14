#ifndef ModelContorl_h
#define ModelContorl_h

#include "Game.h"
#include "Players.h"

enum State
{
	START = 0,
	P1PICK = 1,
	P2PICK = 2,
	GAME = 3,
	END = 4,
	OVER = 5
};

class ModelControl
{
public:
	ModelControl(Game& view);
	~ModelControl();

	void Click();
	void Next();
	void Move(int player, EventType move);
	void Draw();
private:
	Game& _view;
	State _state;
	bool _running;
	int _lives;
	int _frameCount;
	bool _p1move;
	bool _p2move;

	ALLEGRO_SAMPLE* _music;
	ALLEGRO_SAMPLE* _chase;
	ALLEGRO_SAMPLE* _countdown;
	ALLEGRO_SAMPLE* _death;
	ALLEGRO_SAMPLE* _end;
	ALLEGRO_SAMPLE* _thump;

	Pacman _f, _m;
	Ghost _b, _g, _r, _y;

	vector<Player*> _sprites;

	void Start();
	void P1Pick();
	void P2Pick();
	void Maze();
	void End();
	void Countdown();
	bool Collision();
	bool GhostCollision(Player* ghost);
	bool WallCollision(Player* p);
	void Init();
	void Initialization();
	void StartInit();
	void P1PickInit();
	void P2PickInit();
	void MazeInit();

	ALLEGRO_BITMAP* _background;
	ALLEGRO_BITMAP* _textTitle;
	ALLEGRO_BITMAP* _textEnter;
	ALLEGRO_BITMAP* _textP1;
	ALLEGRO_BITMAP* _box;
	ALLEGRO_BITMAP* _textP2;
	ALLEGRO_BITMAP* _maze;
	ALLEGRO_BITMAP* _c3;
	ALLEGRO_BITMAP* _c2;
	ALLEGRO_BITMAP* _c1;
	ALLEGRO_BITMAP* _cs;
};

class MouseObserver : public Observer
{
public:
	MouseObserver(Game& view, ModelControl& mc) : _view(view), _mc(mc) {}
	virtual void Update();
private:
	Game& _view;
	ModelControl& _mc;
};

class KeyboardObserver : public Observer
{
public:
	KeyboardObserver(Game& view, ModelControl& mc) : _view(view), _mc(mc) {}
	virtual void Update();
private:
	Game& _view;
	ModelControl& _mc;
};

class P1KeyboardObserver : public Observer
{
public:
	P1KeyboardObserver(Game& view, ModelControl& mc) : _view(view), _mc(mc) {}
	virtual void Update();
private:
	Game& _view;
	ModelControl& _mc;
};

class P2KeyboardObserver : public Observer
{
public:
	P2KeyboardObserver(Game& view, ModelControl& mc) : _view(view), _mc(mc) {}
	virtual void Update();
private:
	Game& _view;
	ModelControl& _mc;
};

#endif