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
	Room* room5 = new Room("Room5", "Description Room5");
	Room* room6 = new Room("Room6", "Description Room6");
	Room* room7 = new Room("Room7", "Description Room7");

	Item* boat = new Item("Boat", "Description Boat", room0);
	Item* sail = new Item("Sail", "Description Sail", room1, boat);
	Item* oar = new Item("Oar", "Description Oar", room2, boat);
	Item* shell = new Item("Shell", "Description Shell", room3);
	Item* sword = new Item("Sword", "Description Sword", room4);
	Item* shield = new Item("Shield", "Description Shield", room5);
	Item* treasure = new Item("Treasure", "Description Treasure", room7);

	Exit* exit01 = new Exit(DirectionType::NORTH, "Description Exit01", room0, room1, { boat });
	Exit* exit02 = new Exit(DirectionType::SOUTH, "Description Exit02", room0, room2, { boat });
	Exit* exit13 = new Exit(DirectionType::SOUTHEAST, "Description Exit13", room1, room3, { boat });
	Exit* exit31 = new Exit(DirectionType::NORTHWEST, "Description Exit31", room3, room1, { boat });
	Exit* exit23 = new Exit(DirectionType::NORTHEAST, "Description Exit23", room2, room3, { boat });
	Exit* exit32 = new Exit(DirectionType::SOUTHWEST, "Description Exit32", room3, room2, { boat });
	Exit* exit34 = new Exit(DirectionType::NORTH, "Description Exit34", room3, room4, { boat, sail, oar });
	Exit* exit35 = new Exit(DirectionType::SOUTH, "Description Exit35", room3, room5, { boat, sail, oar });
	Exit* exit46 = new Exit(DirectionType::SOUTHEAST, "Description Exit46", room4, room6, { boat });
	Exit* exit56 = new Exit(DirectionType::NORTHEAST, "Description Exit56", room5, room6, { boat });
	Exit* exit67 = new Exit(DirectionType::EAST, "Description Exit67", room6, room7, { boat });

	player = new Player("Player", "Description Player", room0);

	entities.reserve(27);

	// Rooms 8
	entities.push_back(room0);
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(room4);
	entities.push_back(room5);
	entities.push_back(room6);
	entities.push_back(room7);

	// Items 7
	entities.push_back(boat);
	entities.push_back(sail);
	entities.push_back(oar);
	entities.push_back(shell);
	entities.push_back(sword);
	entities.push_back(shield);
	entities.push_back(treasure);

	// Exits 11
	entities.push_back(exit01);
	entities.push_back(exit02);
	entities.push_back(exit13);
	entities.push_back(exit31);
	entities.push_back(exit23);
	entities.push_back(exit32);
	entities.push_back(exit34);
	entities.push_back(exit35);
	entities.push_back(exit46);
	entities.push_back(exit56);
	entities.push_back(exit67);

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