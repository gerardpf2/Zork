#ifndef _Npc_
#define _Npc_

#include "Creature.h"

class Npc : public Creature
{
	public:

		Npc(const char* name, const char* description, Room* room);
		
		virtual ~Npc();
};

#endif