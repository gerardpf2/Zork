#ifndef _CommandListener_
#define _CommandListener_

#include <vector>
#include <string>

using namespace std;

class Player;

class CommandListener
{
	public:

		CommandListener(Player* const player);

		~CommandListener();

		void listen(bool& stop);

		bool process(const string& command, bool& stop) const;

	private:

		void split(const string& command, vector<string>& tokens) const;

		bool resolve(const vector<string>& tokens, bool& stop) const;

	private:

		Player* player = nullptr;

		string playerInput;
};

#endif