#include "Player.h"

#include "Item.h"
#include "Exit.h"
#include <string>
#include "Enemy.h"
#include <assert.h>
#include <iostream>
#include "CombatSystem.h"

Player::Player(const char* name, const char* description, Room* room, CombatSystem* combatSystem, int health) :
	Creature(name, description, EntityType::PLAYER, room, health, 1500), score(0), moves(0), combatSystem(combatSystem)
{
	assert(combatSystem);
}

Player::~Player()
{ }

unsigned int Player::getScore() const
{
	return score;
}

unsigned int Player::getMoves() const
{
	return moves;
}

void Player::incrementScore(unsigned int amount)
{
	score += amount;
}

void Player::incrementMoves(unsigned int amount)
{
	moves += amount;
}

// --- Actions ---

void Player::look() const
{
	// 0 parameters

	getParent()->look();
}

void Player::look(const vector<string>& tokens) const
{
	// 1 parameter (me || _item_)

	assert(tokens.size() == 2);

	string name = tokens[1];

	if(name == "me")
	{
		cout << getName() << endl;
		cout << getDescription() << endl;
	}
	else
	{
		Entity* entity = getParent()->getChild(EntityType::ITEM, name.c_str(), true);

		if(entity) entity->look();
		else
		{
			entity = getParent()->getChild(EntityType::ENEMY, name.c_str());

			if(entity) entity->look();
			else cout << name << " is not here." << endl;
		}
	}
}

void Player::inventory() const
{
	// 0 parameters

	const list<Entity*>* items = getAllChildren(EntityType::ITEM);

	if(!items->empty())
	{
		cout << "Your inventory contains:" << endl;

		for(list<Entity*>::const_iterator it = items->begin(); it != items->end(); ++it)
		{
			cout << "\t" << (*it)->getName();
			if((*it)->hasChildren()) cout << " +";
			cout << endl;
		}
	}
	else cout << "Your inventory is empty." << endl;
}

void Player::go(const vector<string>& tokens)
{
	// 1 parameter (_direction_)

	assert(tokens.size() == 2);

	if(getInCombat())
	{
		cout << "You can not go anywhere if you are in a battle." << endl;
		return;
	}

	string name = tokens[1];
	DirectionType directionType;

	if(name == "e" || name == "east" || name == "East") directionType = DirectionType::EAST;
	else if(name == "w" || name == "west" || name == "West") directionType = DirectionType::WEST;
	else if(name == "n" || name == "north" || name == "North") directionType = DirectionType::NORTH;
	else if(name == "s" || name == "south" || name == "South") directionType = DirectionType::SOUTH;
	else if(name == "ne" || name == "northeast" || name == "Northeast") directionType = DirectionType::NORTHEAST;
	else if(name == "nw" || name == "northwest" || name == "Northwest") directionType = DirectionType::NORTHWEST;
	else if(name == "se" || name == "southeast" || name == "Southeast") directionType = DirectionType::SOUTHEAST;
	else if(name == "sw" || name == "southwest" || name == "Southwest") directionType = DirectionType::SOUTHWEST;
	else
	{
		cout << "Direction " << name << " does not exist." << endl;
		return;
	}

	const list<Entity*>* exits = getParent()->getAllChildren(EntityType::EXIT);

	for(list<Entity*>::const_iterator it = exits->begin(); it != exits->end(); ++it)
	{
		Exit* exit = (Exit*)*it;

		if(exit->getDirectionType() == directionType)
		{
			list<const Item*> missingItems;
			exit->getMissingRequiredItems(this, missingItems);

			if(missingItems.empty())
			{
				assignNewParent((Entity*)exit->getDestination());
				cout << "You take direction " << name << "." << endl;
			}
			else
			{
				string missingItemsNames = missingItems.front()->getName();

				for(list<const Item*>::iterator it = ++missingItems.begin(); it != missingItems.end(); ++it)
					missingItemsNames = missingItemsNames + ", " + (*it)->getName();

				cout << "In order to take direction " << name << " you need the following items: " << missingItemsNames << "." << endl;
			}

			return;
		}
	}

	cout << "Exit at " << name << " does not exist." << endl;
}

void Player::take(const vector<string>& tokens)
{
	// 1 parameter (_item_)

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

			if(item->getCanBeEquipped())
			{
				Item* requiredItemParent = item->getRequiredParentWhenEquipping();

				if(requiredItemParent)
				{
					if(hasChild(requiredItemParent, true))
					{
						item->assignNewParent(requiredItemParent);
						incrementScore(item->getScoreWhenEquipped());
						cout << "You take " << name << ". It is added to " << requiredItemParent->getName() << "." << endl;
					}
					else cout << "You need " << requiredItemParent->getName() << " in order to take " << name << "." << endl;
				}
				else
				{
					item->assignNewParent((Entity*)this);
					incrementScore(item->getScoreWhenEquipped());
					cout << "You take " << name << "." << endl;
				}
			}
			else cout << name << " can not be taken." << endl;
		}
	}
	else cout << name << " is not here." << endl;
}

void Player::drop(const vector<string>& tokens) const
{
	// 1 parameter (_item_)

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

void Player::place(const vector<string>& tokens) const
{
	// 2 parameters (_item_, _item_)

	assert(tokens.size() == 3);

	string name = tokens[1];
	Entity* entity = getChild(EntityType::ITEM, name.c_str(), true);

	if(entity)
	{
		string nameTarget = tokens[2];

		if(name != nameTarget)
		{
			Entity* entityTarget = getChild(EntityType::ITEM, nameTarget.c_str(), true);

			if(entityTarget)
			{
				if(!entityTarget->hasChild(entity))
				{
					if(!entity->hasChild(entityTarget, true))
					{
						Item* item = (Item*)entity;
						Item* requiredItemParent = item->getRequiredParentWhenEquipping();

						if(requiredItemParent && requiredItemParent != entityTarget)
							cout << name << " can only be placed into " << requiredItemParent->getName() << "." << endl;
						else
						{
							item->assignNewParent(entityTarget);
							cout << "You place " << name << " into " << nameTarget << "." << endl;
						}
					}
					else cout << name << " contains " << nameTarget << "." << endl;
				}
				else cout << nameTarget << " already contains " << name << endl;
			}
			else cout << nameTarget << " is not in your inventory." << endl;
		}
		else cout << "Both items are the same." << endl;
	}
	else cout << name << " is not in your inventory." << endl;
}

void Player::attack(const vector<string>& tokens)
{
	// 2 parameters (_item_, _enemy_)

	assert(tokens.size() == 3);

	string itemName = tokens[1];
	Entity* entityItem = getChild(EntityType::ITEM, itemName.c_str(), true);

	if(entityItem)
	{
		string enemyName = tokens[2];
		Entity* entityEnemy = getParent()->getChild(EntityType::ENEMY, enemyName.c_str(), true);

		if(entityEnemy)
		{
			Item* item = (Item*)entityItem;

			if(item->getCanBeUsedToAttack())
			{
				if(canDoAction())
				{
					Enemy* enemy = (Enemy*)entityEnemy;

					doAction();
					setInCombat(true);
					enemy->setInCombat(true);
					enemy->takeDamage(item->getAttackDamage());
				}
				else cout << "You are tired." << endl;
			}
			else cout << itemName << " can not be used to attack." << endl;
		}
		else cout << enemyName << " is not here." << endl;
	}
	else cout << itemName << " is not in your inventory." << endl;
}