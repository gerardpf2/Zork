#include "World.h"

#include "Item.h"
#include "Exit.h"

World::World()
{
	Room* roomA = new Room("RoomA", "... description roomA ...");
	Room* roomB = new Room("RoomB", "... description roomB ...");
	Room* roomC = new Room("RoomC", "... description roomC ...");

	Exit* exitAB = new Exit(EAST, "... description exitAB ...", roomA, roomB);
	Exit* exitBA = new Exit(WEST, "... description exitBA ...", roomB, roomA);
	Exit* exitAC = new Exit(WEST, "... description exitAC ...", roomA, roomC);
	Exit* exitCA = new Exit(EAST, "... description exitCA ...", roomC, roomA);

	Item* itemA = new Item("ItemA", "... description itemA ...", roomA);
	Item* itemB = new Item("ItemB", "... description itemB ...", roomA);
	Item* itemC = new Item("ItemC", "... description itemC ...", roomA);
	Item* itemD = new Item("ItemD", "... description itemD ...", itemC);

	rooms.push_back(roomA);
	rooms.push_back(roomB);
	rooms.push_back(roomC);

	player = new Player("Player", "... description player ...", roomA);
}

World::~World()
{
	for(list<Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) delete *it;

	rooms.clear();
}

Player* World::getPlayer()
{
	return player;
}