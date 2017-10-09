#ifndef _Player_
#define _Player_

#include "Creature.h"

class Player : public Creature
{
	public:

		Player(string name, string description, Room* room);
		virtual ~Player();

		// --- Actions ---

		void look(vector<string>& tokens);
};

#endif