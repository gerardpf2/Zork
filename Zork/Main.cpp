#include "World.h"
#include "CommandListener.h"

int main()
{
	World world;
	CommandListener commandListener(world.getPlayer());

	commandListener.start();
}