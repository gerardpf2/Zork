#include "Creature.h"

#include <iostream>

Creature::Creature(string name, string description, EntityType entityType, Room* room) :
	Entity(name, description, entityType, room)
{

}

Creature::~Creature()
{

}

Room* Creature::getRoom()
{
	return (Room*)getParent();
}

// --- Actions ---

void Creature::look(vector<string>& tokens)
{
	cout << "Creature::look" << endl;
}