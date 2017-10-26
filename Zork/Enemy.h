#ifndef _Enemy_
#define _Enemy_

#include "Creature.h"

class CombatSystem;
class CommandListener;

class Enemy : public Creature
{
	public:

		Enemy(const char* name, const char* description, Room* room, CombatSystem* combatSystem, int health);
		
		virtual ~Enemy();

		void setCommandListener(CommandListener* commandListener);

		virtual void update(clock_t msDeltaTime) override;

	private:

		virtual void die() const override;

	private:

		CombatSystem* combatSystem = nullptr;

		CommandListener* commandListener = nullptr;
};

#endif