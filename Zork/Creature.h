#ifndef _Creature_
#define _Creature_

#include "Entity.h"

class Room;

class Creature : public Entity
{
	public:

		virtual ~Creature();

		bool isAlive() const;

		void takeDamage(unsigned int amount = 1);

		// --- Actions ---

		virtual void look() const override;

	protected:

		Creature(const char* name, const char* description, EntityType entityType, Room* room, int health);

	private:

		int health;
		bool alive;
};

#endif