#ifndef Coin_h
#define Coin_h

#include <iostream>

class Coin
{
public:
	Coin(int x, int y) : _x(x), _y(y), _show(true), _timer(0) {}

	bool Hit(int tlx, int tly, int brx, int bry);
	void DecreaseTimeout();
	bool GetShow() { return _show; }
	int GetX() { return _x; }
	int GetY() { return _y; }

private:
	int _x;
	int _y;
	bool _show;
	int _timer;
};

#endif