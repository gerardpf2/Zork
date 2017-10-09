#ifndef _Exit_
#define _Exit_

#include "Room.h"

enum DirectionType
{
	EAST,
	WEST,
	NORTH,
	SOUTH,
};

class Exit : public Entity
{
	public:

		Exit(DirectionType directionType, string description, Room* origin, Room* destination);
		virtual ~Exit();

		Room* getOrigin();

		Room* getDestination();

		DirectionType getDirectionType();

	private:

		DirectionType directionType;
		Room* destination;
};

#endif