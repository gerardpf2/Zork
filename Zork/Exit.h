#ifndef _Exit_
#define _Exit_

#include "Entity.h"

enum class DirectionType
{
	EAST,
	WEST,
	NORTH,
	SOUTH,
};

class Room;

class Exit : public Entity
{
	public:

		Exit(DirectionType directionType, const char* description, Room* const origin, Room* const destination);
		
		virtual ~Exit();

		Room* getOrigin() const;

		Room* getDestination() const;

		DirectionType getDirectionType() const;

	private:

		DirectionType directionType;

		Room* destination = nullptr;
};

#endif