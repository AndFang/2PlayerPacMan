#ifndef Players_h
#define Players_h

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>
#include <string>
#include <typeinfo>

class Player
{
public:
	int GetX() { return x; };
	void SetX(int next) { x = next; };
	int GetY() { return y; };
	void SetY(int next) { y = next; };
	int GetSpeed() { return speed; };
	void SetSpeed(int next) { speed = next; }
	int GetState() { return state; }
	void SetState(int next) { state = next; }
	bool GetAttack() { return attack; };
	void SetAttack(bool next) { attack = next; };
	bool GetDir() { return dir; };
	void SetDir(bool next) { dir = next; }
	bool Touch(Player& obj);
	std::vector<ALLEGRO_BITMAP*> GetAnnimation(const int state);

	Player& operator=(const Player& obj);
protected:
	int x;
	int y;
	int speed = 5;
	int state = 3; // 0 = hurt, 1 = move, 2 = speed, 3 = stand
	bool attack;
	bool dir = false; // 0 = left, 1 = right
	std::string directory;

	void populateAnnimation(std::string place, bool ghost);

	std::vector<ALLEGRO_BITMAP*> hurtL;
	std::vector<ALLEGRO_BITMAP*> hurtR;
	std::vector<ALLEGRO_BITMAP*> moveL;
	std::vector<ALLEGRO_BITMAP*> moveR;
	std::vector<ALLEGRO_BITMAP*> speedL;
	std::vector<ALLEGRO_BITMAP*> speedR;
	std::vector<ALLEGRO_BITMAP*> standL;
	std::vector<ALLEGRO_BITMAP*> standR;
};

class Pacman : public Player
{
public:
	Pacman() {};
	Pacman(std::string n);
	~Pacman();
};

class Ghost : public Player
{
public:
	Ghost() {};
	Ghost(std::string n);
	~Ghost();
};

#endif /* Players_h */