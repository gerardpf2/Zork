#ifndef _Exit_
#define _Exit_

#include "Room.h"

enum DirectionType
{
	VOID,
	EAST,
	WEST,
	NORTH,
	SOUTH,
};

class Exit : public Entity
{
	public:

		Exit(DirectionType directionTypeOriginToDestination, DirectionType directionTypeDestinationToOrigin, string description, Room* origin, Room* destination);
		virtual ~Exit();

		Room* getOrigin();

		Room* getDestination();

		Room* getOtherRoom(Room* currentRoom);

		DirectionType getDirectionType(Room* currentRoom);

	private:

		DirectionType directionTypeOriginToDestination;
		DirectionType directionTypeDestinationToOrigin;
		Room* destination;
};

#endif