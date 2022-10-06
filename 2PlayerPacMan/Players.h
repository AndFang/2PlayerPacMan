#ifndef Players_h
#define Players_h

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <vector>
#include <string>

class Player
{
public:
	int GetX() { return x; };
	void SetX(int next) { x = next; };
	int GetY() { return y; };
	void SetY(int next) { y = next; };
	int GetSpeed() { return speed; };
	void SetSpeed(int next) { speed = next; }
	bool GetAttack() { return attack; };
	void SetAttack(bool next) { attack = next; };
	bool GetDir() { return dir; };
	void SetDir(bool next) { dir = next; }
	bool Touch(Player &obj);
	std::vector<ALLEGRO_BITMAP*> GetAnnimation(int state);
protected:
	int x;
	int y;
	int speed;
	bool attack;
	bool dir;
	std::string directory;

	std::vector<ALLEGRO_BITMAP*> hurtL;
	std::vector<ALLEGRO_BITMAP*> moveL;
	std::vector<ALLEGRO_BITMAP*> speedL;
	std::vector<ALLEGRO_BITMAP*> standL;
	std::vector<ALLEGRO_BITMAP*> hurtR;
	std::vector<ALLEGRO_BITMAP*> moveR;
	std::vector<ALLEGRO_BITMAP*> speedR;
	std::vector<ALLEGRO_BITMAP*> standR;
};

class Pacman : public Player
{
public:
	Pacman(std::string n);
	~Pacman();
};

class Ghost : public Player
{
public:
	Ghost(std::string n);
	~Ghost();
};

#endif /* Players_h */