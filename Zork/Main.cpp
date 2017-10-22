#include "World.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <Windows.h>
#include "CombatSystem.h"
#include "CommandListener.h"

int main()
{
	World world;
	CommandListener commandListener(world.getPlayer());
	
	world.getEnemy()->setCommandListener(&commandListener); // CommandListener's printDynamic (avoid removing playerInput while Enemy is printing)
	world.getCombatSystem()->setCommandListener(&commandListener); // CommandListener's printDynamic (avoid removing playerInput while CombatSystem is printing)

	bool stop = false;

	commandListener.printHelloMessage();

	while(!stop)
	{
		commandListener.listen(stop); // stop is updated
		world.update();

		if(!world.getPlayer()->isAlive()) // Condition defeat
		{
			cout << "DEFEAT..." << endl;
			commandListener.process("quit", stop);
		}
		else if(world.getPlayer()->getChild(EntityType::ITEM, "Treasure", true)) // Condition victory
		{
			cout << "VICTORY!" << endl;
			commandListener.process("quit", stop);
		}
	}

	commandListener.printGoodbyeMessage();

	Sleep(2000);
}