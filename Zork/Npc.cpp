#include "Npc.h"

Npc::Npc(const char* name, const char* description, Room* const room) :
	Creature(name, description, EntityType::NPC, room)
{ }

Npc::~Npc()
{ }