#include "CommandListener.h"

#include <conio.h>
#include <sstream>
#include "Player.h"
#include <assert.h>
#include <iostream>

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

			if(key == 72) printPreviousHistoryItem(); // Arrow Up
			else if(key == 80) printNextHistoryItem(); // Arrow Down
		}
		else if(key != '\r')
		{
			cout << key;
			playerInput += key;
		}
		else if(playerInput != "")
		{
			string tmpPlayerInput = playerInput;
			playerInput = "";
			cout << endl << endl;
			if(!process(tmpPlayerInput, stop)) cout << "I do not understand your command." << endl;
			player->incrementMoves();
			printCommandEnding();
			if(history.empty() || tmpPlayerInput != *(--history.end())) history.push_back(tmpPlayerInput);
			currentHistoryItem = history.end();
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
	cout << "Thanks for playing. Goodbye!" << endl;
	printCommandEnding();
}

void CommandListener::printDynamic(const string& text, bool ending)
{
	string tmpPlayerInput = playerInput;

	removeCharacters(tmpPlayerInput.size());

	cout << text << endl;

	if(ending) printCommandEnding();

	playerInput = tmpPlayerInput;

	cout << playerInput;
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
			else if(action == "commands" || action == "c") printCommands();
			else if(action == "battle" || action == "b") player->battle();
			else if(action == "inventory" || action == "i") player->inventory();
			else commandOk = false;

			break;
		case 1:
			if(action == "look" || action == "l") player->look(tokens);
			else if(action == "go" || action == "g") player->go(tokens);
			else if(action == "take" || action == "t") player->take(tokens);
			else if(action == "drop" || action == "d") player->drop(tokens);
			else if(action == "attack" || action == "a") player->attack(tokens);
			else if(action == "projectile" || action == "pr") player->projectile(tokens);
			else if(action == "heal" || action == "h") player->heal(tokens);
			else if(action == "move" || action == "m") player->move(tokens);
			else if(action == "rotate" || action == "r") player->rotate(tokens);
			else commandOk = false;

			break;
		case 2:
			if(action == "place" || action == "p") player->place(tokens);
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
	cout << "\tQuits the game." << endl;
	cout << "commands, c" << endl;
	cout << "\tDisplays all the commands." << endl;
	cout << "battle, b" << endl;
	cout << "\tStarts a battle. The player and the enemy must be in the same room." << endl;
	cout << "inventory, i" << endl;
	cout << "\tDisplays all the items that the player owns." << endl;
	cout << "look, l ['me', _item_ or _enemy_]" << endl;
	cout << "\tShows information about the specified entity. Parameters are optional.\n\t'me' refers to the player itself. _item_ and _enemy_ are ingame names." << endl;
	cout << "go, g _direction_" << endl;
	cout << "\tThe player goes to another room. _direction_ can be: 'n', 's', 'e',\n\t'w', 'ne', 'nw', 'se' or 'sw'. 'north' and 'North' are valid too (and so on)." << endl;
	cout << "take, t _item_" << endl;
	cout << "\tThe player takes an item. The player and the item must be in the same\n\troom. The item must not be owned by the player. _item_ is an ingame name." << endl;
	cout << "drop, d _item_" << endl;
	cout << "\tThe player drops an item. The item must be owned by the player. _item_\n\tis an ingame name." << endl;
	cout << "place, p _item_ _item_" << endl;
	cout << "\tThe player places an item inside another one. Both must be owned by the\n\tplayer. _item_ is an ingame name." << endl;
	cout << "(combat mode) attack, a _item_" << endl;
	cout << "\tThe player attacks the enemy using the specified item. The item must be\n\towned by the player. _item_ is an ingame name." << endl;
	cout << "(combat mode) projectile, pr _item_" << endl;
	cout << "\tThe player throws the specified item to the enemy. The item must be owned\n\tby the player. The item is dropped. _item_ is an ingame name." << endl;
	cout << "(combat mode) heal, h _item_" << endl;
	cout << "\tThe player heals using the specified item. The item must be\n\towned by the player. _item_ is an ingame name." << endl;
	cout << "(combat mode) move, m _combatDirection_" << endl;
	cout << "\tThe player moves in the specified direction. _combatDirection_ can be: 'u',\n\t'd', 'l' or 'r'. 'up' and 'Up' are valid too (and so on)." << endl;
	cout << "(combat mode) rotate, r _combatDirection_" << endl;
	cout << "\tThe player rotates in the specified direction. _combatDirection_ can be: 'u',\n\t'd', 'l' or 'r'. 'up' and 'Up' are valid too (and so on)." << endl;
}

void CommandListener::printCommandEnding() const
{
	assert(player);

	cout << "------------------------------ Health: " << player->getHealth() << ", Score: " << player->getScore() << ", Moves: " << player->getMoves() << endl;
}

void CommandListener::removeCharacters(unsigned int amount)
{
	while(!playerInput.empty() && amount-- > 0)
	{
		cout << "\b \b";
		playerInput.pop_back();
	}
}