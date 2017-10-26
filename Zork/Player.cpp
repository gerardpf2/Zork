#include "Player.h"

#include "Item.h"
#include "Exit.h"
#include <string>
#include "Enemy.h"
#include <assert.h>
#include <iostream>
#include "CombatSystem.h"

Player::Player(const char* name, const char* description, Room* room, CombatSystem* combatSystem, int health) :
	Creature(name, description, EntityType::PLAYER, room, health, 2000), combatSystem(combatSystem)
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

void Player::die() const
{
	cout << "You lose." << endl;
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

void Player::battle()
{
	// 0 parameters

	if(getInCombat())
	{
		cout << "You are already in a battle." << endl;
		return;
	}

	const list<Entity*>* enemies = getParent()->getAllChildren(EntityType::ENEMY);

	if(!enemies->empty())
	{
		Enemy* enemy = ((Enemy*)enemies->front());

		if(enemy->isAlive())
		{
			setInCombat(true);
			((Enemy*)enemies->front())->setInCombat(true);

			combatSystem->printBattlefield();
			cout << "Battle starts NOW!" << endl;
		}
		else cout << enemy->getName() << " is already dead." << endl;
	}
	else cout << "There is no enemy here." << endl;
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
		cout << "You cannot go anywhere if you are in a battle." << endl;
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
						item->removeScoreWhenEquipped();
						cout << "You take " << name << ". It is added to " << requiredItemParent->getName() << "." << endl;
					}
					else cout << "You need " << requiredItemParent->getName() << " in order to take " << name << "." << endl;
				}
				else
				{
					item->assignNewParent((Entity*)this);
					incrementScore(item->getScoreWhenEquipped());
					item->removeScoreWhenEquipped();
					cout << "You take " << name << "." << endl;
				}
			}
			else cout << name << " cannot be taken." << endl;
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

void Player::attack(const vector<string>& tokens)
{
	// 2 parameters (_item_)

	assert(tokens.size() == 2);

	if(!getInCombat())
	{
		cout << "You are not in a battle." << endl;
		return;
	}

	string itemName = tokens[1];
	Entity* entityItem = getChild(EntityType::ITEM, itemName.c_str(), true);

	if(entityItem)
	{
		const list<Entity*>* entitiesEnemy = getParent()->getAllChildren(EntityType::ENEMY);

		if(!entitiesEnemy->empty())
		{
			Item* item = (Item*)entityItem;

			if(item->getCanBeUsedToAttack())
			{
				if(canDoAction())
				{
					Entity* entityEnemy = entitiesEnemy->front();

					if(combatSystem->playerAttackCanHit())
					{
						if(!combatSystem->playerMissAttack())
						{
							Enemy* enemy = (Enemy*)entityEnemy;

							enemy->takeDamage(item->getAttackDamage());
							cout << "You attack " << enemy->getName() << " using " << itemName << ". " << enemy->getName() << " loses " << item->getAttackDamage() << " hp." << endl;

							if(!enemy->isAlive())
							{
								setInCombat(false);
								cout << "You win!" << endl;
							}
						}
						else cout << "You missed..." << endl;

						doAction();
					}
					else
					{
						if(combatSystem->playerFacingEnemy()) cout << "You are not close enough to " << entityEnemy->getName() << "." << endl;
						else cout << "You are not facing " << entityEnemy->getName() << "." << endl;
					}
				}
				else cout << "You are tired." << endl;
			}
			else cout << itemName << " cannot be used to attack." << endl;
		}
		else cout << "There is no enemy here." << endl;
	}
	else cout << itemName << " is not in your inventory." << endl;
}

void Player::projectile(const vector<string>& tokens)
{
	// 2 parameters (_item_)

	assert(tokens.size() == 2);

	if(!getInCombat())
	{
		cout << "You are not in a battle." << endl;
		return;
	}

	string itemName = tokens[1];
	Entity* entityItem = getChild(EntityType::ITEM, itemName.c_str(), true);

	if(entityItem)
	{
		const list<Entity*>* entitiesEnemy = getParent()->getAllChildren(EntityType::ENEMY);

		if(!entitiesEnemy->empty())
		{
			Item* item = (Item*)entityItem;

			if(canDoAction())
			{
				Entity* entityEnemy = entitiesEnemy->front();

				if(combatSystem->playerProjectileCanHit())
				{
					if(!combatSystem->playerMissProjectile())
					{
						Enemy* enemy = (Enemy*)entityEnemy;

						enemy->takeDamage(item->getProjectileDamage());
						cout << "You attack " << enemy->getName() << " using " << itemName << " as a projectile. " << enemy->getName() << " loses " << item->getProjectileDamage() << " hp." << endl;

						if(!enemy->isAlive())
						{
							setInCombat(false);
							cout << "You win!" << endl;
						}
					}
					else cout << "You missed..." << endl;

					doAction();
				}
				else cout << "You are not facing " << entityEnemy->getName() << "." << endl;

				item->assignNewParent((Entity*)getParent());
			}
			else cout << "You are tired." << endl;
		}
		else cout << "There is no enemy here." << endl;
	}
	else cout << itemName << " is not in your inventory." << endl;
}

void Player::heal(const vector<string>& tokens)
{
	// 2 parameters (_item_)

	assert(tokens.size() == 2);

	if(!getInCombat())
	{
		cout << "You are not in a battle." << endl;
		return;
	}

	string itemName = tokens[1];
	Entity* entityItem = getChild(EntityType::ITEM, itemName.c_str(), true);

	if(entityItem)
	{
		Item* item = (Item*)entityItem;

		if(item->getCanBeUsedToHeal())
		{
			if(canIncrementHealth())
			{
				if(canDoAction())
				{
					unsigned int amountHealed = incrementHealth(item->getHealAmount());
					item->removeHealAmount();
					cout << "You heal for " << amountHealed << " using " << itemName << "." << endl;

					doAction();
				}
				else cout << "You are tired." << endl;
			}
			else cout << "Your health is full." << endl;
		}
		else cout << itemName << " cannot be used to heal." << endl;
	}
	else cout << itemName << " is not in your inventory." << endl;
}

void Player::move(const vector<string>& tokens)
{
	// 1 parameter (_combatDirection_)

	assert(tokens.size() == 2);

	if(!getInCombat())
	{
		cout << "You are not in a battle." << endl;
		return;
	}

	string name = tokens[1];
	CombatDirectionType combatDirectionType;

	if(name == "u" || name == "up" || name == "Up") combatDirectionType = CombatDirectionType::UP;
	else if(name == "d" || name == "down" || name == "Down") combatDirectionType = CombatDirectionType::DOWN;
	else if(name == "l" || name == "left" || name == "Left") combatDirectionType = CombatDirectionType::LEFT;
	else if(name == "r" || name == "right" || name == "Right") combatDirectionType = CombatDirectionType::RIGHT;
	else
	{
		cout << "Combat direction " << name << " does not exist." << endl;
		return;
	}

	if(combatSystem->canMovePlayer(combatDirectionType))
	{
		if(canDoAction())
		{
			doAction();
			combatSystem->movePlayer(combatDirectionType);
			cout << "You move to " << name << "." << endl;
		}
		else cout << "You are tired." << endl;
	}
	else cout << "You cannot move to " << name << "." << endl;
}

void Player::rotate(const vector<string>& tokens)
{
	// 1 parameter (_combatDirection_)

	assert(tokens.size() == 2);

	if(!getInCombat())
	{
		cout << "You are not in a battle." << endl;
		return;
	}

	string name = tokens[1];

	CombatDirectionType combatDirectionType;

	if(name == "u" || name == "up" || name == "Up") combatDirectionType = CombatDirectionType::UP;
	else if(name == "d" || name == "down" || name == "Down") combatDirectionType = CombatDirectionType::DOWN;
	else if(name == "l" || name == "left" || name == "Left") combatDirectionType = CombatDirectionType::LEFT;
	else if(name == "r" || name == "right" || name == "Right") combatDirectionType = CombatDirectionType::RIGHT;
	else
	{
		cout << "Combat direction " << name << " does not exist." << endl;
		return;
	}

	if(combatSystem->canRotatePlayer(combatDirectionType))
	{
		if(canDoAction())
		{
			doAction();
			combatSystem->rotatePlayer(combatDirectionType);
			cout << "You rotate to " << name << "." << endl;
		}
		else cout << "You are tired." << endl;
	}
	else cout << "You cannot rotate to " << name << "." << endl;
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