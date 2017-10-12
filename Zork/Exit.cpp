#include "Exit.h"

#include "Room.h"
#include <assert.h>

Exit::Exit(DirectionType directionType, const char* description, Room* const origin, Room* const destination) :
	Entity("", description, EntityType::EXIT, origin), directionType(directionType), destination(destination)
{ }

Exit::~Exit()
{ }

Room* Exit::getOrigin() const
{
	assert(getParent());

	return (Room*)getParent();
}

Room* Exit::getDestination() const
{
	return destination;
}

DirectionType Exit::getDirectionType() const
{
	return directionType;
}