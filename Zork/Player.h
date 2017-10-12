#ifndef _Player_
#define _Player_

#include "Creature.h"

class Player : public Creature
{
	public:

		Player(const char* name, const char* description, Room* room);
		
		virtual ~Player();

		// --- Actions ---

		bool look(const vector<string>& tokens) const override;
};

#endif