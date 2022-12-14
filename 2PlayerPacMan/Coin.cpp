#include "Coin.h"

bool Coin::Hit(int tlx, int tly, int brx, int bry)
{
	if (!_show)
		return false;

	bool inside = false;

	if (tlx <= _x && _x <= brx && tly <= _y && _y <= bry)
		inside = true;
	if (tlx <= _x + 30 && _x + 30 <= brx && tly <= _y && _y <= bry)
		inside = true;
	if (tlx <= _x && _x <= brx && tly <= _y + 30 && _y + 30 <= bry)
		inside = true;
	if (tlx <= _x + 30 && _x + 30 <= brx && tly <= _y + 30 && _y + 30 <= bry)
		inside = true;

	if (inside)
	{
		_show = false;
		_timer = (int)(((double)rand() / (RAND_MAX)) * 60) + 60;
		return true;
	}
	
	return false;
}

void Coin::DecreaseTimeout()
{
	if (_timer)
		_timer -= 1;
	
	if (_timer == 0)
		_show = true;
}
