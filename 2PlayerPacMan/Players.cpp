#include "Players.h"

bool Player::Touch(Player& obj)
{
	return false;
}

std::vector<ALLEGRO_BITMAP*> Player::GetAnnimation(int state)
{

}

Pacman::Pacman(std::string n)
{
	directory = "Assets/" + n + "/";
}

Pacman::~Pacman()
{

}

Ghost::Ghost(std::string n)
{
	directory = "Assets/" + n + "/";
}

Ghost::~Ghost()
{

}