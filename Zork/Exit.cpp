#include "Exit.h"

Exit::Exit(DirectionType directionType, string description, Room* origin, Room* destination) :
	Entity("", description, EXIT, origin), directionType(directionType), destination(destination)
{

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

DirectionType Exit::getDirectionType()
{
	return directionType;
}