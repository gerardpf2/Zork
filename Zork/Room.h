#ifndef _Room_
#define _Room_

#include "Entity.h"

class Room : public Entity
{
	public:

		Room(string name, string description);
		virtual ~Room();
};

#endif