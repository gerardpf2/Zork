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
				text += " attacks you! You lose 1 hp.";

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
				CombatDirectionType combatDirectionType = combatSystem->enemyFindMove();

				if(combatSystem->canMoveEnemy(combatDirectionType))
				{
					combatSystem->moveEnemy(combatDirectionType);

					string text = getName();
					text += " moves trying to catch you.";

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
					text += " rotates trying to see you.";

					commandListener->printDynamic(text, true);
				}
			}
		}

		doAction();
	}
}

void Enemy::die() const
{
	lockItems(false, true);
}