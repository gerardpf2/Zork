#include "World.h"

#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "Enemy.h"
#include "Player.h"
#include "CombatSystem.h"

World::World()
{
	srand((unsigned int)time(nullptr)); // CombatSystem hit/miss

	lastUpdateTime = clock();

	Room* room0 = new Room("Turtle Island", "You are on a peaceful turtle-shaped island.");
	Room* room1 = new Room("Rum Island", "It seems that a battle has taken place right here... Maybe you can find a weapon around.");
	Room* room2 = new Room("Pearl Island", "You are on a very nice island. You can see some bright spots here and there.");
	Room* room3 = new Room("Parrot Island", "Really strong flows of water can be seen near here.");
	Room* room4 = new Room("Pirate Island", "You are on the island frequented by the most dangerous pirates.");

	combatSystem = new CombatSystem(5, 5, 4, 2, CombatDirectionType::UP, 0, 2, CombatDirectionType::DOWN, 6, 4);

	enemy = new Enemy("Enemy", "He is a very strong pirate. And he has stolen your treasure!", room4, combatSystem, 10);
	player = new Player("Player", "You are a tiny but brave pirate.", room0, combatSystem, 5);

	Item* boat = new Item("Boat", "It is an old and half broken wooden boat.", room0, 10, 0, 2, 0);
	Item* sword = new Item("Sword", "It is a weak sword but it can still be used.", room1, 5, 1, 1, 0);
	Item* coconut = new Item("Coconut", "Small but delicious coconut. Probably you can use it once if you are hurt.", room1, 5, 0, 1, 2);
	Item* shell = new Item("Shell", "It is nice but apparently not very useful.", room2, 5, 0, 1, 0);
	Item* oar = new Item("Oar", "It is a wooden oar, and it can be used to improve your boat.", room2, 10, 0, 1, 0, boat);
	Item* sail = new Item("Sail", "It has some holes but it can still be used in a boat.", room3, 10, 0, 1, 0, boat);
	Item* treasure = new Item("Treasure", "YOUR treasure!", enemy, 100, 0, 1, 0);

	Exit* exit01 = new Exit("North. Calm water flow. You need a boat.", DirectionType::NORTH, room0, room1, { boat });
	Exit* exit10 = new Exit("South. Calm water flow. You need a boat.", DirectionType::SOUTH, room1, room0, { boat });
	Exit* exit02 = new Exit("South. Calm water flow. You need a boat.", DirectionType::SOUTH, room0, room2, { boat });
	Exit* exit20 = new Exit("North. Calm water flow. You need a boat.", DirectionType::NORTH, room2, room0, { boat });
	Exit* exit13 = new Exit("Southeast. Calm water flow. You need a boat.", DirectionType::SOUTHEAST, room1, room3, { boat });
	Exit* exit31 = new Exit("Northwest. Calm water flow. You need a boat.", DirectionType::NORTHWEST, room3, room1, { boat });
	Exit* exit23 = new Exit("Northeast. Calm water flow. You need a boat.", DirectionType::NORTHEAST, room2, room3, { boat });
	Exit* exit32 = new Exit("Southwest. Calm water flow. You need a boat.", DirectionType::SOUTHWEST, room3, room2, { boat });
	Exit* exit34 = new Exit("East. Really strong water flow. You need a boat, an oar and a sail.", DirectionType::EAST, room3, room4, { boat, sail, oar });

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
	for(int i = (int)entities.size() - 1; i >= 0; --i)
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