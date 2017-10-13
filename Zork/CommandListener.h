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

		CommandListener(const Player* player);

		~CommandListener();

		void listen(bool& stop);

		bool process(const string& command, bool& stop) const;

	private:

		void split(const string& command, vector<string>& tokens) const;

		bool resolve(const vector<string>& tokens, bool& stop) const;

		void removeCharacters(unsigned int amount);

		void printPreviousHistoryItem();

		void printNextHistoryItem();

	private:

		const Player* player = nullptr;

		string playerInput;

		list<string> history;

		list<string>::iterator currentHistoryItem;
};

#endif