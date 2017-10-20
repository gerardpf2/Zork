#ifndef _Player_
#define _Player_

#include "Creature.h"

class Player : public Creature
{
	public:

		Player(const char* name, const char* description, Room* room, int health);
		
		virtual ~Player();

		// --- Actions ---

		void look() const override;

		void look(const vector<string>& tokens) const;

		void inventory() const;

		void go(const vector<string>& tokens);

		void take(const vector<string>& tokens) const;

		void drop(const vector<string>& tokens) const;

		void place(const vector<string>& tokens) const;
};

#endif