#ifndef _Item_
#define _Item_

#include "Entity.h"

class Item : public Entity
{
	public:

		Item(const char* name, const char* description, Entity* parent, unsigned int scoreWhenEquipped, bool canBeUsedToAttack, unsigned int attackDamage, unsigned int projectileDamage, Item* requiredParentWhenEquipping = nullptr);

		virtual ~Item();

		bool getCanBeEquipped() const;

		void setCanBeEquipped(bool canBeEquipped);

		bool getCanBeUsedToAttack() const;

		unsigned int getAttackDamage() const;

		unsigned int getProjectileDamage() const;

		unsigned int getScoreWhenEquipped();

		Item* getRequiredParentWhenEquipping() const;

		// --- Actions ---

		virtual void look() const override;

	private:

		bool canBeEquipped = true;

		bool canBeUsedToAttack = false;

		unsigned int attackDamage = 0;

		unsigned int projectileDamage = 0;

		unsigned int scoreWhenEquipped = 0;

		Item* requiredParentWhenEquipping = nullptr;
};

#endif