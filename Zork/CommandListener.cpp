#include "CommandListener.h"

#include <conio.h>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "Player.h"

CommandListener::CommandListener(const Player* player) :
	player(player)
{ }

CommandListener::~CommandListener()
{ }

void CommandListener::listen(bool& stop)
{
	if(_kbhit())
	{
		char key = _getch();

		if(key == '\b' && !playerInput.empty())
		{
			cout << "\b \b";
			playerInput.pop_back();
		}
		else if(key != '\r')
		{
			cout << key;
			playerInput += key;
		}
		else
		{
			cout << endl;
			if(!process(playerInput, stop)) cout << ". . ." << endl;
			playerInput = "";
		}
	}
}

bool CommandListener::process(const string& command, bool& stop) const
{
	vector<string> tokens;
	split(command, tokens);

	return resolve(tokens, stop);
}

void CommandListener::split(const string& command, vector<string>& tokens) const
{
	string token;
	stringstream commandTokens(command);

	while(getline(commandTokens, token, ' ')) tokens.push_back(token);
}

bool CommandListener::resolve(const vector<string>& tokens, bool& stop) const
{
	assert(player);

	if(tokens.empty()) return false;

	string action = tokens[0];

	if(action == "quit" || action == "q") stop = true;
	else if(action == "look" || action == "l") return player->look(tokens);

	return false;
}