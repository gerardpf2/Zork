#ifndef _Player_
#define _Player_

#include "Creature.h"

class CombatSystem;

class Player : public Creature
{
	public:

		Player(const char* name, const char* description, Room* room, CombatSystem* combatSystem, int health);
		
		virtual ~Player();

		unsigned int getScore() const;

		unsigned int getMoves() const;

		void incrementScore(unsigned int amount);

		void incrementMoves(unsigned int amount = 1);

		// --- Actions ---

		void look() const override;

		void look(const vector<string>& tokens) const;

		void battle();

		void inventory() const;

		void go(const vector<string>& tokens);

		void take(const vector<string>& tokens);

		void drop(const vector<string>& tokens) const;

		void attack(const vector<string>& tokens);

		void projectile(const vector<string>& tokens);

		void heal(const vector<string>& tokens);

		void move(const vector<string>& tokens);

		void rotate(const vector<string>& tokens);

		void place(const vector<string>& tokens) const;

	private:

		void die() override;

	private:

		unsigned int score = 0;

		unsigned int moves = 0;

		CombatSystem* combatSystem = nullptr;
};

#endif