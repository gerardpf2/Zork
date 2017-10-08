#ifndef _World_
#define _World_

#include <list>
#include "Room.h"
#include "Player.h"

class World
{
	public:

		World();
		~World();

	private:

		Player* player;
		list<Room*> rooms;

};

#endif