#include "Player.h"

#include <iostream>

Player::Player(string name, string description, Room* room) :
	Creature(name, description, PLAYER, room)
{

}

Player::~Player()
{

}

// --- Actions ---

void Player::look(vector<string>& tokens)
{
	cout << "Player::look" << endl;
}