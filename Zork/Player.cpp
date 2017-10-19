#include "Player.h"

#include "Item.h"
#include <string>
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

	if(name == "me" || name == getName())
	{
		cout << getName() << endl;
		cout << getDescription() << endl;
	}
	else
	{
		Entity* entity = getParent()->getChild(name.c_str(), true);

		if(entity) entity->look();
		else cout << name << " is not here." << endl;
	}
}

void Player::inventory() const
{
	// 0 parameters

	printChildren("Your inventory contains:", EntityType::ITEM, "Your inventory is empty.");
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

	string name = tokens[1];
	Entity* entity = getParent()->getChild(EntityType::ITEM, name.c_str(), true);

	if(entity)
	{
		if(hasChild(entity, true))
			cout << name << " is already in your inventory." << endl;
		else
		{
			Item* item = (Item*)entity;
			Item* requiredItemParent = item->getRequiredParentWhenEquipping();

			if(requiredItemParent)
			{
				if(hasChild(requiredItemParent, true))
				{
					entity->assignNewParent(requiredItemParent);
					cout << "You take " << name << ". It is added to " << requiredItemParent->getName() << "." << endl;
				}
				else cout << "You need " << requiredItemParent->getName() << " in order to take " << name << "." << endl;
			}
			else
			{
				entity->assignNewParent((Entity*)this);
				cout << "You take " << name << "." << endl;
			}
		}
	}
	else cout << name << " is not here." << endl;
}

void Player::drop(const vector<string>& tokens) const
{
	// 1 parameter (_itemName_)

	assert(tokens.size() == 2);

	string name = tokens[1];
	Entity* entity = getChild(EntityType::ITEM, name.c_str(), true);

	if(entity)
	{
		entity->assignNewParent((Entity*)getParent());
		cout << "You drop " << name << "." << endl;
	}
	else cout << name << " is not in your inventory." << endl;
}