#ifndef _Creature_
#define _Creature_

#include "Room.h"

class Creature : public Entity
{
	public:

		Creature(string name, string description, Room* room);
		virtual ~Creature();

		Room* getRoom();
};

#endif