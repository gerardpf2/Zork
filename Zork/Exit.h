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

		Exit(DirectionType directionType, const char* description, Room* origin, const Room* destination);
		
		virtual ~Exit();

		const Room* getOrigin() const;

		const Room* getDestination() const;

		DirectionType getDirectionType() const;

	private:

		DirectionType directionType;

		const Room* destination = nullptr;
};

#endif