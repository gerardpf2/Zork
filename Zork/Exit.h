#ifndef _Exit_
#define _Exit_

#include <set>
#include "Entity.h"

enum class DirectionType
{
	EAST,
	WEST,
	NORTH,
	SOUTH,
	NORTHEAST,
	NORTHWEST,
	SOUTHEAST,
	SOUTHWEST,
};

class Room;
class Item;
class Player;

class Exit : public Entity
{
	public:

		Exit(const char* name, const char* description, DirectionType directionType, Room* origin, const Room* destination, const initializer_list<const Item*>& requiredItems = { });

		virtual ~Exit();

		const Room* getOrigin() const;

		const Room* getDestination() const;

		DirectionType getDirectionType() const;

		void getMissingRequiredItems(const Player* player, list<const Item*>& missingItems) const;

	private:

		DirectionType directionType;

		const Room* destination = nullptr;

		set<const Item*> requiredItems;
};

#endif