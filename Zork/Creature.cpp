#include "Creature.h"

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