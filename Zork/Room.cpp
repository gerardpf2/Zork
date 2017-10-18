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

	// Exits

	const list<Entity*>* exits = getAllChildren(EntityType::EXIT);

	if(!exits->empty())
	{
		cout << "Exits" << endl;

		for(list<Entity*>::const_iterator it = exits->begin(); it != exits->end(); ++it)
			cout << "   " << (*it)->getName() << endl;
	}

	// Items

	const list<Entity*>* items = getAllChildren(EntityType::ITEM);

	if(!items->empty())
	{
		cout << "Items" << endl;

		for(list<Entity*>::const_iterator it = items->begin(); it != items->end(); ++it)
			cout << "   " << (*it)->getName() << endl;
	}

	// Npcs

	const list<Entity*>* npcs = getAllChildren(EntityType::NPC);

	if(!npcs->empty())
	{
		cout << "Npcs" << endl;

		for(list<Entity*>::const_iterator it = npcs->begin(); it != npcs->end(); ++it)
			cout << "   " << (*it)->getName() << endl;
	}
}