#include "CommandListener.h"

#include <conio.h>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "Player.h"

CommandListener::CommandListener(const Player* player) :
	player(player)
{
	assert(player);

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
			if(!process(playerInput, stop)) cout << "I do not understand your command." << endl;
			cout << "------------------------------" << endl;
			if(history.empty() || playerInput != *(--history.end())) history.push_back(playerInput);
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

	bool commandOk = true;

	string action = tokens[0];
	unsigned int parametersCount = tokens.size() - 1;

	switch(parametersCount)
	{
		case 0:
			if(action == "quit" || action == "q") stop = true;
			else if(action == "help" || action == "h") printHelp();
			else if(action == "look" || action == "l") player->look();
			else if(action == "inventory" || action == "i") player->inventory();
			else commandOk = false;

			break;
		case 1:
			if(action == "look" || action == "l") player->look(tokens);
			else if(action == "go" || action == "g") player->go(tokens);
			else if(action == "take" || action == "t") player->take(tokens);
			else if(action == "drop" || action == "d") player->drop(tokens);
			else commandOk = false;

			break;
		default:
			commandOk = false;
	}

	return commandOk;
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

void CommandListener::printHelp() const
{
	cout << "Commands" << endl;
	cout << "\tquit, q" << endl;
	cout << "\thelp, h" << endl;
	cout << "\tinventory, i" << endl;
	cout << "\tlook, l [me, _entity_]" << endl;
	cout << "\tgo, g _direction_" << endl;
	cout << "\ttake, t _item_" << endl;
	cout << "\tdrop, d _item_" << endl;
}