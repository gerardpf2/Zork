#ifndef _World_
#define _World_

#include <list>

using namespace std;

class Room;
class Player;

class World
{
	public:

		World();

		~World();

		const Player* getPlayer() const;

		void update() const;

	private:

		Player* player = nullptr;

		list<Room*> rooms;
};

#endif