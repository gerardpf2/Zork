#ifndef _World_
#define _World_

#include <time.h>
#include <vector>

using namespace std;

class Enemy;
class Entity;
class Player;
class CombatSystem;

class World
{
	public:

		World();

		~World();

		Enemy* getEnemy() const;

		Player* getPlayer() const;

		CombatSystem* getCombatSystem() const;

		void update();

	private:

		Enemy* enemy = nullptr;

		Player* player = nullptr;

		CombatSystem* combatSystem = nullptr;

		vector<Entity*> entities;

		clock_t lastUpdateTime = -1;
};

#endif