#include "Player.h"

Player::Player(const char* name, const char* description, Room* const room) :
	Creature(name, description, EntityType::PLAYER, room)
{ }

Player::~Player()
{ }

// --- Actions ---

#include <iostream>

bool Player::look(const vector<string>& tokens) const
{
	cout << "Player::look" << endl;

	return true;
}