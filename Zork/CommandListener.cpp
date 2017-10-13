#include "CommandListener.h"

#include <conio.h>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "Player.h"

CommandListener::CommandListener(const Player* player) :
	player(player)
{
	currentHistoryItem = history.end();
}

CommandListener::~CommandListener()
{
	history.clear();
}

void CommandListener::listen(bool& stop)
{
	if(_kbhit())
	{
		char key = _getch();

		if(key == '\b') removeCharacters(1);
		else if(key == -32)
		{
			key = _getch();

			// Arrow Up
			if(key == 72) printPreviousHistoryItem();
			// Arrow Down
			else if(key == 80) printNextHistoryItem();
		}
		else if(key != '\r')
		{
			cout << key;
			playerInput += key;
		}
		else if(playerInput != "")
		{
			cout << endl;
			if(!process(playerInput, stop)) cout << ". . ." << endl;
			if(history.empty() || (!history.empty() && playerInput != *(--history.end()))) history.push_back(playerInput);
			currentHistoryItem = history.end();
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
	assert(!tokens.empty());

	string action = tokens[0];

	if(action == "quit" || action == "q") stop = true;
	else if(action == "look" || action == "l") return player->look(tokens);

	return false;
}

void CommandListener::removeCharacters(unsigned int amount)
{
	while(!playerInput.empty() && amount-- > 0)
	{
		cout << "\b \b";
		playerInput.pop_back();
	}
}

void CommandListener::printPreviousHistoryItem()
{
	if(currentHistoryItem != history.begin())
	{
		--currentHistoryItem;

		removeCharacters(playerInput.size());

		cout << (playerInput = *currentHistoryItem);
	}
}

void CommandListener::printNextHistoryItem()
{
	if(currentHistoryItem != history.end() && currentHistoryItem != --history.end())
	{
		++currentHistoryItem;

		removeCharacters(playerInput.size());

		cout << (playerInput = *currentHistoryItem);
	}
}