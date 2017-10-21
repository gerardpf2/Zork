#include "World.h"
#include "Enemy.h"
#include "CombatSystem.h"
#include "CommandListener.h"

int main()
{
	World world;
	CommandListener commandListener(world.getPlayer());
	
	world.getEnemy()->setCommandListener(&commandListener);
	world.getCombatSystem()->setCommandListener(&commandListener);

	bool stop = false;

	commandListener.printHelloMessage();

	while(!stop)
	{
		commandListener.listen(stop);
		world.update();
	}

	commandListener.printGoodbyeMessage();
}