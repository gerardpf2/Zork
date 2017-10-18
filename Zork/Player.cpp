#include "Player.h"

#include <assert.h>
#include <iostream>

Player::Player(const char* name, const char* description, Room* room) :
	Creature(name, description, EntityType::PLAYER, room)
{ }

Player::~Player()
{ }

// --- Actions ---

void Player::look() const
{
	// 0 parameters

	getParent()->look();
}

void Player::look(const vector<string>& tokens) const
{
	// 1 parameter (me, _entityName_)

	assert(tokens.size() == 2);

	string name = tokens[1];

	if(name == "me")
	{
		cout << getName() << endl;
		cout << getDescription() << endl;
	}
	else
	{
		Entity* entity = getParent()->getChild(name.c_str(), true);
		if(entity) entity->look();
	}
}

void Player::inventory() const
{
	// 0 parameters
}

void Player::go(const vector<string>& tokens) const
{
	// 1 parameter (_directionType_)

	assert(tokens.size() == 2);
}

void Player::take(const vector<string>& tokens) const
{
	// 1 parameter (_itemName_)

	assert(tokens.size() == 2);
}

void Player::drop(const vector<string>& tokens) const
{
	// 1 parameter (_itemName_)

	assert(tokens.size() == 2);
}