#include "Creature.h"

Creature::Creature(string name, string description, Room* room) :
	Entity(name, description, CREATURE, room)
{

}

Creature::~Creature()
{

}

Room* Creature::getRoom()
{
	return (Room*)getParent();
}