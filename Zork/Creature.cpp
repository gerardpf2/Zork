#include "Creature.h"

#include "Room.h"
#include <assert.h>

Creature::Creature(const char* name, const char* description, EntityType entityType, Room* room) :
	Entity(name, description, entityType, room)
{
	assert(room);
}

Creature::~Creature()
{ }

const Room* Creature::getRoom() const
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