#include "CommandListener.h"

#include <conio.h>
#include <sstream>
#include <iostream>
#include <assert.h>
#include "Player.h"

CommandListener::CommandListener(Player* player) :
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
			cout << endl << endl;
			if(!process(playerInput, stop)) cout << "I do not understand your command." << endl;
			player->incrementMoves();
			printCommandEnding();
			if(history.empty() || playerInput != *(--history.end())) history.push_back(playerInput);
			currentHistoryItem = history.end();
			playerInput = "";
		}
	}
}

void CommandListener::printHelloMessage() const
{
	cout << "Welcome!" << endl;
	cout << "Type 'commands' or 'c' in order to see all existing commands." << endl;
	printCommandEnding();
}

void CommandListener::printGoodbyeMessage() const
{
	cout << "Goodbye!" << endl;
	printCommandEnding();
}

void CommandListener::printDynamic(const string& text)
{
	if(!playerInput.empty())
	{
		string tmpPlayerInput = playerInput;

		removeCharacters(playerInput.size());

		cout << text << endl;

		playerInput = tmpPlayerInput;

		cout << playerInput;
	}
	else cout << text << endl;
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
			else if(action == "look" || action == "l") player->look();
			else if (action == "commands" || action == "c") printCommands();
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
		case 2:
			if(action == "place" || action == "p") player->place(tokens);
			else if(action == "attack" || action == "a") player->attack(tokens);
			else commandOk = false;

			break;
		default:
			commandOk = false;
	}

	return commandOk;
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

void CommandListener::printCommands() const
{
	cout << "quit, q" << endl;
	cout << "help, h" << endl;
	cout << "inventory, i" << endl;
	cout << "look, l [me, _item_ || _enemy_]" << endl;
	cout << "go, g _direction_" << endl;
	cout << "take, t _item_" << endl;
	cout << "drop, d _item_" << endl;
	cout << "place, p _item_ _item_" << endl;
	cout << "attack, a _item_ _enemy_" << endl;
}

void CommandListener::printCommandEnding() const
{
	assert(player);

	cout << "------------------------------ Score: " << player->getScore() << ", Moves: " << player->getMoves() << endl;
}

void CommandListener::removeCharacters(unsigned int amount)
{
	while(!playerInput.empty() && amount-- > 0)
	{
		cout << "\b \b";
		playerInput.pop_back();
	}
}