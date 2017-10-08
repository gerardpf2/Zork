#ifndef _Player_
#define _Player_

#include "Creature.h"

class Player : public Creature
{
	public:

		// EntityType PLAYER
		Player(string name, string description, Room* room);
		virtual ~Player();
};

#endif