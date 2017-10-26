#include "Creature.h"

#include "Room.h"
#include <assert.h>
#include <iostream>

Creature::Creature(const char* name, const char* description, EntityType entityType, Room* room, int health, int msNextAction, int currentMsNextAction) :
	Entity(name, description, entityType, room), health(health), maxHealth(health), msNextAction(msNextAction), currentMsNextAction(currentMsNextAction)
{
	assert(room);

	if(!(alive = health > 0)) die();
}

Creature::~Creature()
{ }

bool Creature::isAlive() const
{
	return alive;
}

int Creature::getHealth() const
{
	return health;
}

void Creature::takeDamage(unsigned int amount)
{
	if(alive && (health -= amount) <= 0)
	{
		die();
		alive = false;
	}
}

bool Creature::canIncrementHealth() const
{
	return health < maxHealth;
}

unsigned int Creature::incrementHealth(unsigned int amount)
{
	unsigned int amountHealed = maxHealth - health;
	if(amountHealed > amount) amountHealed = amount;

	health += amountHealed;

	return amountHealed;
}

bool Creature::getInCombat() const
{
	return inCombat;
}

void Creature::setInCombat(bool inCombat)
{
	this->inCombat = inCombat;
}

bool Creature::canDoAction() const
{
	return currentMsNextAction <= 0;
}

void Creature::doAction()
{
	currentMsNextAction = msNextAction;
}

void Creature::update(clock_t msDeltaTime)
{
	if(inCombat)
	{
		if(alive)
		{
			if(currentMsNextAction > 0) currentMsNextAction -= msDeltaTime;
		}
		else inCombat = false;
	}
}

void Creature::die() const
{ }

// --- Actions ---

void Creature::look() const
{
	if(!alive) cout << "(Dead) ";

	cout << getName() << endl;
	cout << getDescription() << endl;

	const list<Entity*>* items = getAllChildren(EntityType::ITEM);

	if(!items->empty())
	{
		cout << "This is carrying:" << endl;

		for(list<Entity*>::const_iterator it = items->begin(); it != items->end(); ++it)
		{
			cout << "\t" << (*it)->getName();
			if((*it)->hasChildren()) cout << " +";
			cout << endl;
		}
	}
}