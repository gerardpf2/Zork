#include "Exit.h"

#include "Room.h"
#include <assert.h>

Exit::Exit(DirectionType directionType, const char* description, Room* origin, const Room* destination) :
	Entity("", description, EntityType::EXIT, origin), directionType(directionType), destination(destination)
{ }

Exit::~Exit()
{ }

const Room* Exit::getOrigin() const
{
	assert(getParent());

	return (Room*)getParent();
}

const Room* Exit::getDestination() const
{
	return destination;
}

DirectionType Exit::getDirectionType() const
{
	return directionType;
}