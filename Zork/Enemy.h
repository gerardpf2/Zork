#ifndef _Enemy_
#define _Enemy_

#include "Creature.h"

class Enemy : public Creature
{
	public:

		Enemy(const char* name, const char* description, Room* room, int health);
		
		virtual ~Enemy();
};

#endif