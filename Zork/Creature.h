#ifndef _Creature_
#define _Creature_

#include "Room.h"

class Creature : public Entity
{
	protected:

		Creature(string name, string description, EntityType entityType, Room* room);

	public:

		virtual ~Creature();

		Room* getRoom();

		// --- Actions ---

		virtual void look(vector<string>& tokens);
};

#endif