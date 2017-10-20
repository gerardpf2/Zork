#include "Room.h"

#include "Exit.h"
#include <iostream>

Room::Room(const char* name, const char* description) :
	Entity(name, description, EntityType::ROOM, nullptr)
{ }

Room::~Room()
{ }

// --- Actions ---

void Room::look() const
{
	cout << getName() << endl;
	cout << getDescription() << endl;

	// Items

	const list<Entity*>* items = getAllChildren(EntityType::ITEM);

	if(!items->empty())
	{
		cout << "This contains (Items):" << endl;

		for(list<Entity*>::const_iterator it = items->begin(); it != items->end(); ++it)
		{
			cout << "\t" << (*it)->getName();
			if((*it)->hasChildren()) cout << " +";
			cout << endl;
		}
	}

	// Exits

	const list<Entity*>* exits = getAllChildren(EntityType::EXIT);

	if(!exits->empty())
	{
		cout << "This contains (Exits):" << endl;

		for(list<Entity*>::const_iterator it = exits->begin(); it != exits->end(); ++it)
			cout << "\t" << (*it)->getDescription() << endl;
	}

	// Enemies

	const list<Entity*>* enemies = getAllChildren(EntityType::ENEMY);

	if(!enemies->empty())
	{
		cout << "This contains (Enemies):" << endl;

		for(list<Entity*>::const_iterator it = enemies->begin(); it != enemies->end(); ++it)
		{
			cout << "\t" << (*it)->getName();
			if((*it)->hasChildren()) cout << " +";
			cout << endl;
		}
	}
}