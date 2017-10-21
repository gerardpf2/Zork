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

		bool getInCombat() const;

		void setInCombat(bool inCombat);

		bool canDoAction() const;

		void doAction();

		virtual void update(clock_t msDeltaTime) override;

		// --- Actions ---

		virtual void look() const override;

	protected:

		Creature(const char* name, const char* description, EntityType entityType, Room* room, int health, int msNextAction);

		virtual void die();

	private:

		int health;

		bool alive;

		bool inCombat;

		int msNextAction;

		int currentMsNextAction = 0;
};

#endif