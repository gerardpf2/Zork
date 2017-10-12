#include "World.h"
#include "CommandListener.h"

int main()
{
	World world;
	CommandListener commandListener(world.getPlayer());
	
	bool stop = false;

	string initialCommand = "look";
	commandListener.process(initialCommand, stop);

	while(!stop)
	{
		commandListener.listen(stop);
		world.update();
	}
}