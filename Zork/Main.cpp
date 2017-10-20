#include "World.h"
#include "CommandListener.h"

int main()
{
	World world;
	CommandListener commandListener(world.getPlayer());
	
	bool stop = false;

	commandListener.printHelloMessage();

	while(!stop)
	{
		commandListener.listen(stop);
		world.update();
	}

	commandListener.printGoodbyeMessage();
}