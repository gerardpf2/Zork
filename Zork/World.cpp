#include "World.h"

#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "Player.h"

World::World()
{
	lastUpdateTime = clock();

	Room* room0 = new Room("Room0", "Description Room0");
	Room* room1 = new Room("Room1", "Description Room1");
	Room* room2 = new Room("Room2", "Description Room2");
	Room* room3 = new Room("Room3", "Description Room3");
	Room* room4 = new Room("Room4", "Description Room4");

	Item* boat = new Item("Boat", "Description Boat", room0);
	Item* sword = new Item("Sword", "Description Sword", room0);
	Item* shield = new Item("Shield", "Description Shield", room0);
	Item* oar = new Item("Oar", "Description Oar", room0, boat);
	Item* sail = new Item("Sail", "Description Sail", room0, boat);
	Item* shell = new Item("Shell", "Description Shell", room0);

	/* Item* boat = new Item("Boat", "Description Boat", room0);
	Item* sword = new Item("Sword", "Description Sword", room1);
	Item* shield = new Item("Shield", "Description Shield", room2);
	Item* oar = new Item("Oar", "Description Oar", room2, boat);
	Item* sail = new Item("Sail", "Description Sail", room3, boat);
	Item* shell = new Item("Shell", "Description Shell", room4); */

	Exit* exit01 = new Exit("NorthRoom0", "Description Exit01", DirectionType::NORTH, room0, room1, { boat });
	Exit* exit10 = new Exit("SouthRoom1", "Description Exit10", DirectionType::SOUTH, room1, room0, { boat });
	Exit* exit02 = new Exit("SouthRoom0", "Description Exit02", DirectionType::SOUTH, room0, room2, { boat });
	Exit* exit20 = new Exit("NorthRoom2", "Description Exit20", DirectionType::NORTH, room2, room0, { boat });
	Exit* exit13 = new Exit("SoutheastRoom1", "Description Exit13", DirectionType::SOUTHEAST, room1, room3, { boat });
	Exit* exit31 = new Exit("NorthwestRoom3", "Description Exit31", DirectionType::NORTHWEST, room3, room1, { boat });
	Exit* exit23 = new Exit("NortheastRoom2", "Description Exit23", DirectionType::NORTHEAST, room2, room3, { boat });
	Exit* exit32 = new Exit("SouthwestRoom3", "Description Exit32", DirectionType::SOUTHWEST, room3, room2, { boat });
	Exit* exit34 = new Exit("EastRoom3", "Description Exit34", DirectionType::EAST, room3, room4, { boat, sail, oar });

	player = new Player("Player", "Description Player", room0);

	entities.reserve(21);

	// Rooms 5
	entities.push_back(room0);
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(room4);

	// Items 6
	entities.push_back(boat);
	entities.push_back(sword);
	entities.push_back(shield);
	entities.push_back(oar);
	entities.push_back(sail);
	entities.push_back(shell);

	// Exits 9
	entities.push_back(exit01);
	entities.push_back(exit10);
	entities.push_back(exit02);
	entities.push_back(exit20);
	entities.push_back(exit13);
	entities.push_back(exit31);
	entities.push_back(exit23);
	entities.push_back(exit32);
	entities.push_back(exit34);

	// Creatures 1
	entities.push_back(player);
}

World::~World()
{
	for(unsigned int i = 0; i < entities.size(); ++i)
	{
		delete entities[i];
		entities[i] = nullptr;
	}

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
		entities[i]->update(msDeltaTime);

	lastUpdateTime = currentUpdateTime;
}