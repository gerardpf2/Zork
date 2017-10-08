#include "Player.h"

Player::Player(string name, string description, Room* room) :
	Creature(name, description, PLAYER, room)
{

}

Player::~Player()
{

}