#ifndef _CommandListener_
#define _CommandListener_

#include <vector>
#include "Player.h"

class CommandListener
{
	public:

		CommandListener(Player* player);
		~CommandListener();

		void start();

	private:

		Player* player;
		bool stopListening = false;

		void stop();

		void processCommand(string& command);

		void splitCommand(string& command, vector<string>& tokens);

		void resolveCommand(vector<string>& tokens);
};

#endif