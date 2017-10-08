#include "World.h"

#include "Item.h"
#include "Exit.h"

World::World()
{
	Room* roomA = new Room("RoomA", "... description roomA ...");
	Room* roomB = new Room("RoomB", "... description roomB ...");
	Room* roomC = new Room("RoomC", "... description roomC ...");

	Exit* exitAB = new Exit(EAST, WEST, "... description exitAB ...", roomA, roomB);
	Exit* exitAC = new Exit(WEST, EAST, "... description exitAC ...", roomA, roomC);

	Item* itemA = new Item("ItemA", "... description itemA ...", roomA);
	Item* itemB = new Item("ItemB", "... description itemB ...", roomA);
	Item* itemC = new Item("ItemC", "... description itemC ...", roomA);

	rooms.push_back(roomA);
	rooms.push_back(roomB);
	rooms.push_back(roomC);

	player = new Player("Player", "... description player ...", roomA);
}

World::~World()
{

}