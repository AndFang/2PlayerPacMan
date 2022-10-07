#include "Players.h"

bool Player::Touch(Player& obj)
{
	return false;
}

std::vector<ALLEGRO_BITMAP*> Player::GetAnnimation(const int next)
{
	switch (next)
	{
	case(0):
		if (dir)
			return hurtR;
		else
			return hurtL;
		break;
	case(1):
		if (dir)
			return moveR;
		else
			return moveL;
		break;
	case(2):
		if (dir)
			return speedR;
		else
			return speedL;
		break;
	case(3):
		if (dir)
			return standR;
		else
			return standL;
		break;
	default:
		throw "NO STATE";
	}

	state = next;
}

Player& Player::operator=(const Player& obj)
{
	directory = obj.directory;

	hurtL.clear();
	hurtR.clear();
	moveL.clear();
	moveR.clear();
	speedL.clear();
	speedR.clear();
	standL.clear();
	standR.clear();

	populateAnnimation(obj.directory, typeid(Ghost) == typeid(obj));

	return *this;
}

void Player::populateAnnimation(std::string place, bool ghost)
{
	hurtL.push_back(al_load_bitmap((place + "L/Hurt/Hurt0.png").c_str()));
	hurtL.push_back(al_load_bitmap((place + "L/Hurt/Hurt1.png").c_str()));
	hurtL.push_back(al_load_bitmap((place + "L/Hurt/Hurt2.png").c_str()));
	hurtL.push_back(al_load_bitmap((place + "L/Hurt/Hurt3.png").c_str()));

	hurtR.push_back(al_load_bitmap((place + "R/Hurt/Hurt0.png").c_str()));
	hurtR.push_back(al_load_bitmap((place + "R/Hurt/Hurt1.png").c_str()));
	hurtR.push_back(al_load_bitmap((place + "R/Hurt/Hurt2.png").c_str()));
	hurtR.push_back(al_load_bitmap((place + "R/Hurt/Hurt3.png").c_str()));

	moveL.push_back(al_load_bitmap((place + "L/Move/Move0.png").c_str()));
	moveL.push_back(al_load_bitmap((place + "L/Move/Move1.png").c_str()));
	moveL.push_back(al_load_bitmap((place + "L/Move/Move2.png").c_str()));
	moveL.push_back(al_load_bitmap((place + "L/Move/Move3.png").c_str()));

	moveR.push_back(al_load_bitmap((place + "R/Move/Move0.png").c_str()));
	moveR.push_back(al_load_bitmap((place + "R/Move/Move1.png").c_str()));
	moveR.push_back(al_load_bitmap((place + "R/Move/Move2.png").c_str()));
	moveR.push_back(al_load_bitmap((place + "R/Move/Move3.png").c_str()));

	speedL.push_back(al_load_bitmap((place + "L/Speed/Speed0.png").c_str()));
	speedL.push_back(al_load_bitmap((place + "L/Speed/Speed1.png").c_str()));
	speedL.push_back(al_load_bitmap((place + "L/Speed/Speed2.png").c_str()));
	speedL.push_back(al_load_bitmap((place + "L/Speed/Speed3.png").c_str()));

	speedR.push_back(al_load_bitmap((place + "R/Speed/Speed0.png").c_str()));
	speedR.push_back(al_load_bitmap((place + "R/Speed/Speed1.png").c_str()));
	speedR.push_back(al_load_bitmap((place + "R/Speed/Speed2.png").c_str()));
	speedR.push_back(al_load_bitmap((place + "R/Speed/Speed3.png").c_str()));

	standL.push_back(al_load_bitmap((place + "L/Stand/Stand0.png").c_str()));
	standL.push_back(al_load_bitmap((place + "L/Stand/Stand1.png").c_str()));
	standL.push_back(al_load_bitmap((place + "L/Stand/Stand2.png").c_str()));
	standL.push_back(al_load_bitmap((place + "L/Stand/Stand3.png").c_str()));

	standR.push_back(al_load_bitmap((directory + "R/Stand/Stand0.png").c_str()));
	standR.push_back(al_load_bitmap((directory + "R/Stand/Stand1.png").c_str()));
	standR.push_back(al_load_bitmap((directory + "R/Stand/Stand2.png").c_str()));
	standR.push_back(al_load_bitmap((directory + "R/Stand/Stand3.png").c_str()));

	if (ghost)
	{
		moveL.push_back(al_load_bitmap((place + "L/Move/Move4.png").c_str()));
		moveL.push_back(al_load_bitmap((place + "L/Move/Move5.png").c_str()));

		moveR.push_back(al_load_bitmap((place + "R/Move/Move4.png").c_str()));
		moveR.push_back(al_load_bitmap((place + "R/Move/Move5.png").c_str()));
	}
}

Pacman::Pacman(std::string n)
{
	directory = "Assets/" + n + "/";

	populateAnnimation(directory, false);
}

Pacman::~Pacman()
{
	for (auto i : hurtL)
		al_destroy_bitmap(i);
	for (auto i : hurtR)
		al_destroy_bitmap(i);
	for (auto i : moveL)
		al_destroy_bitmap(i);
	for (auto i : moveR)
		al_destroy_bitmap(i);
	for (auto i : speedL)
		al_destroy_bitmap(i);
	for (auto i : speedR)
		al_destroy_bitmap(i);
	for (auto i : standL)
		al_destroy_bitmap(i);
	for (auto i : standR)
		al_destroy_bitmap(i);
}

Ghost::Ghost(std::string n)
{
	directory = "Assets/" + n + "/";

	populateAnnimation(directory, true);
}

Ghost::~Ghost()
{
	for (auto i : hurtL)
		al_destroy_bitmap(i);
	for (auto i : hurtR)
		al_destroy_bitmap(i);
	for (auto i : moveL)
		al_destroy_bitmap(i);
	for (auto i : moveR)
		al_destroy_bitmap(i);
	for (auto i : speedL)
		al_destroy_bitmap(i);
	for (auto i : speedR)
		al_destroy_bitmap(i);
	for (auto i : standL)
		al_destroy_bitmap(i);
	for (auto i : standR)
		al_destroy_bitmap(i);
}