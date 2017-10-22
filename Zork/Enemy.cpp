#include "Enemy.h"

#include "Player.h"
#include <assert.h>
#include "CombatSystem.h"
#include "CommandListener.h"

Enemy::Enemy(const char* name, const char* description, Room* room, CombatSystem* combatSystem, int health) :
	Creature(name, description, EntityType::ENEMY, room, health, 4000, 2000), combatSystem(combatSystem)
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

		if(combatSystem->enemyAttackCanHit())
		{
			if(!combatSystem->enemyMissAttack())
			{
				const list<Entity*>* players = getParent()->getAllChildren(EntityType::PLAYER);

				if(!players->empty())
					((Player*)players->front())->takeDamage(1);

				string text = getName();
				text += " attacks you!";

				commandListener->printDynamic(text, true);
			}
			else
			{
				string text = getName();
				text += " attacks you, but misses...";

				commandListener->printDynamic(text, true);
			}
		}
		else
		{
			if(combatSystem->enemyFacingPlayer() || combatSystem->enemyRotationSame())
			{
				int rowIncrement = 0;
				int columnIncrement = 0;

				combatSystem->enemyFindMove(rowIncrement, columnIncrement);

				if(combatSystem->canMoveEnemy(rowIncrement, columnIncrement))
				{
					combatSystem->moveEnemy(rowIncrement, columnIncrement);

					string text = getName();
					text += " moves.";

					commandListener->printDynamic(text, true);
				}
			}
			else
			{
				CombatDirectionType combatDirectionType = combatSystem->enemyFindRotation();

				if(combatSystem->canRotateEnemy(combatDirectionType))
				{
					combatSystem->rotateEnemy(combatDirectionType);

					string text = getName();
					text += " rotates.";

					commandListener->printDynamic(text, true);
				}
			}
		}

		doAction();
	}
}

void Enemy::die()
{
	lockItems(false, true);
}