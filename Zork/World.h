#ifndef _World_
#define _World_

#include <vector>
#include <time.h>

using namespace std;

class Entity;
class Player;

class World
{
	public:

		World();

		~World();

		const Player* getPlayer() const;

		void update();

	private:

		Player* player = nullptr;

		vector<Entity*> entities;

		clock_t lastUpdateTime;
};

#endif