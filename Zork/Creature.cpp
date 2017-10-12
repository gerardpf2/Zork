#include "Creature.h"

#include "Room.h"
#include <assert.h>

Creature::Creature(const char* name, const char* description, EntityType entityType, Room* const room) :
	Entity(name, description, entityType, room)
{ }

Creature::~Creature()
{ }

Room* Creature::getRoom() const
{
	assert(getParent());

	return (Room*)getParent();
}

// --- Actions ---

#include <iostream>

bool Creature::look(const vector<string>& tokens) const
{
	cout << "Creature::look" << endl;

	return true;
}