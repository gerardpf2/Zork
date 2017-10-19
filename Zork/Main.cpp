#include "World.h"
#include "CommandListener.h"

int main()
{
	World world;
	CommandListener commandListener(world.getPlayer());
	
	bool stop = false;

	// commandListener.helloMessage();

	// commandListener.process("help", stop);
	// commandListener.process("look", stop);

	while(!stop)
	{
		commandListener.listen(stop);
		world.update();
	}

	// commandListener.goodbyeMessage();
}