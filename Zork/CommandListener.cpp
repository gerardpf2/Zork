#include "CommandListener.h"

#include <sstream>
#include <iostream>

CommandListener::CommandListener(Player* player) :
	player(player)
{

}

CommandListener::~CommandListener()
{

}

void CommandListener::start()
{
	cout << "CommandListener START" << endl;

	string initialCommand = "look";
	processCommand(initialCommand);

	string command;
	while(!stopListening && getline(cin, command)) processCommand(command);
}

void CommandListener::stop()
{
	cout << "CommandListener STOP" << endl;

	stopListening = true;
}

void CommandListener::processCommand(string& command)
{
	cout << "Command: " << command << endl;

	vector<string> tokens;
	splitCommand(command, tokens);

	resolveCommand(tokens);
}

void CommandListener::splitCommand(string& command, vector<string>& tokens)
{
	string token;
	stringstream commandTokens(command);

	while(getline(commandTokens, token, ' ')) tokens.push_back(token);
}

void CommandListener::resolveCommand(vector<string>& tokens)
{
	if(tokens.empty()) return;

	string action = tokens[0];

	if(action == "quit" || action == "q") stop();
	else if(action == "look" || action == "l") player->look(tokens);
}