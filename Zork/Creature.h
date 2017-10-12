#ifndef _Creature_
#define _Creature_

#include "Entity.h"

class Room;

class Creature : public Entity
{
	public:

		virtual ~Creature();

		const Room* getRoom() const;

		// --- Actions ---

		virtual bool look(const vector<string>& tokens) const override;

	protected:

		Creature(const char* name, const char* description, EntityType entityType, Room* room);
};

#endif