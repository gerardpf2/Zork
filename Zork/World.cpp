#include "World.h"

#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "Enemy.h"
#include "Player.h"
#include "CombatSystem.h"

World::World()
{
	srand((unsigned int)time(nullptr));

	lastUpdateTime = clock();

	Room* room0 = new Room("Room0", "Description Room0");
	Room* room1 = new Room("Room1", "Description Room1");
	Room* room2 = new Room("Room2", "Description Room2");
	Room* room3 = new Room("Room3", "Description Room3");
	Room* room4 = new Room("Room4", "Description Room4");

	combatSystem = new CombatSystem(5, 5, 4, 2, CombatDirectionType::UP, 0, 2, CombatDirectionType::DOWN, 6, 4);

	enemy = new Enemy("Enemy", "Description Enemy", room4, combatSystem, 10);
	player = new Player("Player", "Description Player", room0, combatSystem, 5);

	Item* boat = new Item("Boat", "Description Boat", room0, 10, 0, 2, 0);
	Item* sword = new Item("Sword", "Description Sword", room1, 5, 1, 1, 0);
	Item* coconut = new Item("Coconut", "Description Coconut", room1, 5, 0, 1, 1);
	Item* oar = new Item("Oar", "Description Oar", room2, 10, 0, 1, 0, boat);
	Item* sail = new Item("Sail", "Description Sail", room3, 10, 0, 1, 0, boat);
	Item* shell = new Item("Shell", "Description Shell", room2, 5, 0, 1, 0);
	Item* treasure = new Item("Treasure", "Description Treasure", enemy, 100, 0, 1, 0);

	Exit* exit01 = new Exit("Description Exit01", DirectionType::NORTH, room0, room1, { boat });
	Exit* exit10 = new Exit("Description Exit10", DirectionType::SOUTH, room1, room0, { boat });
	Exit* exit02 = new Exit("Description Exit02", DirectionType::SOUTH, room0, room2, { boat });
	Exit* exit20 = new Exit("Description Exit20", DirectionType::NORTH, room2, room0, { boat });
	Exit* exit13 = new Exit("Description Exit13", DirectionType::SOUTHEAST, room1, room3, { boat });
	Exit* exit31 = new Exit("Description Exit31", DirectionType::NORTHWEST, room3, room1, { boat });
	Exit* exit23 = new Exit("Description Exit23", DirectionType::NORTHEAST, room2, room3, { boat });
	Exit* exit32 = new Exit("Description Exit32", DirectionType::SOUTHWEST, room3, room2, { boat });
	Exit* exit34 = new Exit("Description Exit34", DirectionType::EAST, room3, room4, { boat, sail, oar });

	entities.reserve(23);

	// Rooms 5
	entities.push_back(room0);
	entities.push_back(room1);
	entities.push_back(room2);
	entities.push_back(room3);
	entities.push_back(room4);

	// Items 7
	entities.push_back(boat);
	entities.push_back(sword);
	entities.push_back(coconut);
	entities.push_back(oar);
	entities.push_back(sail);
	entities.push_back(shell);
	entities.push_back(treasure);

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

	// Creatures 2
	entities.push_back(enemy);
	entities.push_back(player);

	if(enemy->isAlive()) enemy->lockItems(true, true); // Player cannot take Enemy items
}

World::~World()
{
	for(int i = entities.size() - 1; i >= 0; --i)
	{
		delete entities[i];
		entities[i] = nullptr;
	}

	entities.clear();

	delete combatSystem;
	combatSystem = nullptr;
}

Enemy* World::getEnemy() const
{
	return enemy;
}

Player* World::getPlayer() const
{
	return player;
}

CombatSystem* World::getCombatSystem() const
{
	return combatSystem;
}

void World::update()
{
	clock_t currentUpdateTime = clock();
	clock_t msDeltaTime = currentUpdateTime - lastUpdateTime;

	for(unsigned int i = 0; i < entities.size(); ++i)
		entities[i]->update(msDeltaTime);

	lastUpdateTime = currentUpdateTime;
}