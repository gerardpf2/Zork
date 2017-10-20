#ifndef _CommandListener_
#define _CommandListener_

#include <list>
#include <vector>
#include <string>

using namespace std;

class Player;

class CommandListener
{
	public:

		CommandListener(Player* player);

		~CommandListener();

		void listen(bool& stop);

		void printHelloMessage() const;

		void printGoodbyeMessage() const;

	private:

		bool process(const string& command, bool& stop) const;

		void split(const string& command, vector<string>& tokens) const;

		bool resolve(const vector<string>& tokens, bool& stop) const;

		void removeCharacters(unsigned int amount);

		void printPreviousHistoryItem();

		void printNextHistoryItem();

		void printCommands() const;

	private:

		Player* player = nullptr;

		string playerInput;

		list<string> history;

		list<string>::iterator currentHistoryItem;
};

#endif