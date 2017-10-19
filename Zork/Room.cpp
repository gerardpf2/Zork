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

	printChildren("This contains (Exits):", EntityType::EXIT);
	printChildren("This contains (Items):", EntityType::ITEM);
	printChildren("This contains (Npcs):", EntityType::NPC);
}