#include "Enemy.h"

#include <assert.h>
#include "CombatSystem.h"
#include "CommandListener.h"

Enemy::Enemy(const char* name, const char* description, Room* room, CombatSystem* combatSystem, int health) :
	Creature(name, description, EntityType::ENEMY, room, health, 2000), combatSystem(combatSystem)
{
	assert(combatSystem);
}

Enemy::~Enemy()
{ }

void Enemy::setCommandListener(CommandListener* commandListener)
{
	assert(commandListener);

	this->commandListener = commandListener;
}

#include <iostream>

void Enemy::update(clock_t msDeltaTime)
{
	Creature::update(msDeltaTime);

	if(getInCombat() && canDoAction())
	{
		assert(combatSystem);
		assert(commandListener);

		if(combatSystem->canMoveEnemy(1, 0)) combatSystem->moveEnemy(1, 0); //

		doAction();
		commandListener->printDynamic("Action");
	}
}

void Enemy::die()
{
	unlockItems(true);
}