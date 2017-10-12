#ifndef _Creature_
#define _Creature_

#include "Entity.h"

class Room;

class Creature : public Entity
{
	protected:

		Creature(const char* name, const char* description, EntityType entityType, Room* const room);

	public:

		virtual ~Creature();

		Room* getRoom() const;

		// --- Actions ---

		virtual bool look(const vector<string>& tokens) const override;
};

#endif