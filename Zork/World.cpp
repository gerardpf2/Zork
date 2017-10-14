#include "World.h"

#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "Player.h"

World::World()
{
	lastUpdateTime = clock();

	Room* roomA = new Room("RoomA", "... description roomA ...");
	Room* roomB = new Room("RoomB", "... description roomB ...");
	Room* roomC = new Room("RoomC", "... description roomC ...");

	Exit* exitAB = new Exit(DirectionType::EAST, "... description exitAB ...", roomA, roomB);
	Exit* exitBA = new Exit(DirectionType::WEST, "... description exitBA ...", roomB, roomA);
	Exit* exitAC = new Exit(DirectionType::WEST, "... description exitAC ...", roomA, roomC);
	Exit* exitCA = new Exit(DirectionType::EAST, "... description exitCA ...", roomC, roomA);

	Item* itemA = new Item("ItemA", "... description itemA ...", roomA);
	Item* itemB = new Item("ItemB", "... description itemB ...", roomA);
	Item* itemC = new Item("ItemC", "... description itemC ...", roomA);
	Item* itemD = new Item("ItemD", "... description itemD ...", itemC);

	player = new Player("Player", "... description player ...", roomA);

	entities.reserve(12);

	// Rooms 3
	entities.push_back(roomA);
	entities.push_back(roomB);
	entities.push_back(roomC);

	// Exits 4
	entities.push_back(exitAB);
	entities.push_back(exitBA);
	entities.push_back(exitAC);
	entities.push_back(exitCA);

	// Items 4
	entities.push_back(itemA);
	entities.push_back(itemB);
	entities.push_back(itemC);
	entities.push_back(itemD);

	// Creatures 1
	entities.push_back(player);
}

World::~World()
{
	for(unsigned int i = 0; i < entities.size(); ++i)
		delete entities[i];

	entities.clear();
}

const Player* World::getPlayer() const
{
	return player;
}

void World::update()
{
	clock_t currentUpdateTime = clock();
	clock_t msDeltaTime = currentUpdateTime - lastUpdateTime;

	for(unsigned int i = 0; i < entities.size(); ++i)
		if(entities[i]) entities[i]->update(msDeltaTime);

	lastUpdateTime = currentUpdateTime;
}