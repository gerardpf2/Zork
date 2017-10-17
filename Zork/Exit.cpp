#include "Exit.h"

#include "Room.h"
#include "Item.h"
#include "Player.h"
#include <assert.h>

Exit::Exit(DirectionType directionType, const char* description, Room* origin, const Room* destination, const initializer_list<const Item*>& requiredItems) :
	Entity("", description, EntityType::EXIT, origin), directionType(directionType), destination(destination), requiredItems(requiredItems)
{
	assert(origin);
	assert(destination);
}

Exit::~Exit()
{
	requiredItems.clear();
}

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

void Exit::getMissingRequiredItems(const Player* player, list<const Item*>& missingItems) const
{
	assert(player);
	assert(missingItems.empty());

	for(set<const Item*>::iterator it = requiredItems.begin(); it != requiredItems.end(); ++it)
		if(!player->hasChild(*it, true)) missingItems.push_back(*it);
}