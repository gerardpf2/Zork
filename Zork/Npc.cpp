#include "Npc.h"

Npc::Npc(string name, string description, Room* room) :
	Creature(name, description, NPC, room)
{

}

Npc::~Npc()
{

}