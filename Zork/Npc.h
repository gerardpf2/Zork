#ifndef _Npc_
#define _Npc_

#include "Creature.h"

class Npc : public Creature
{
	public:

		Npc(string name, string description, Room* room);
		virtual ~Npc();
};

#endif