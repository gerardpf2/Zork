#include "Creature.h"

#include "Room.h"
#include <assert.h>
#include <iostream>

Creature::Creature(const char* name, const char* description, EntityType entityType, Room* room, int health) :
	Entity(name, description, entityType, room), health(health)
{
	assert(room);

	alive = health > 0;
}

Creature::~Creature()
{ }

bool Creature::isAlive() const
{
	return alive;
}

void Creature::takeDamage(unsigned int amount)
{
	alive = (health -= amount) > 0;
}

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