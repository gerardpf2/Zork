#include "Exit.h"

Exit::Exit(DirectionType directionTypeOriginToDestination, DirectionType directionTypeDestinationToOrigin, string description, Room* origin, Room* destination) :
	Entity("", description, EXIT, origin), directionTypeOriginToDestination(directionTypeOriginToDestination), directionTypeDestinationToOrigin(directionTypeDestinationToOrigin), destination(destination)
{
	destination->addEntity(this);
}

Exit::~Exit()
{

}

Room* Exit::getOrigin()
{
	return (Room*)getParent();
}

Room* Exit::getDestination()
{
	return destination;
}

Room* Exit::getOtherRoom(Room* currentRoom)
{
	if(getOrigin() == currentRoom) return getDestination();
	if(getDestination() == currentRoom) return getOrigin();
	return NULL; // There is no connection between this and currentRoom
}

DirectionType Exit::getDirectionType(Room* currentRoom)
{
	if (getOrigin() == currentRoom) return directionTypeOriginToDestination;
	if (getDestination() == currentRoom) return directionTypeDestinationToOrigin;
	return VOID; // There is no connection between this and currentRoom
}