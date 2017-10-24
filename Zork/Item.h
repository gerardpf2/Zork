#ifndef _Item_
#define _Item_

#include "Entity.h"

class Item : public Entity
{
	public:

		Item(const char* name, const char* description, Entity* parent, unsigned int scoreWhenEquipped, unsigned int attackDamage, unsigned int projectileDamage, unsigned int healAmount, Item* requiredParentWhenEquipping = nullptr);

		virtual ~Item();

		bool getCanBeEquipped() const;

		void setCanBeEquipped(bool canBeEquipped);

		bool getCanBeUsedToAttack() const;

		unsigned int getAttackDamage() const;

		unsigned int getProjectileDamage() const;

		bool getCanBeUsedToHeal() const;

		unsigned int getHealAmount() const;

		void removeHealAmount();

		unsigned int getScoreWhenEquipped() const;

		void removeScoreWhenEquipped();

		Item* getRequiredParentWhenEquipping() const;

		// --- Actions ---

		virtual void look() const override;

	private:

		bool canBeEquipped = true;

		unsigned int healAmount = 0;

		unsigned int attackDamage = 0;

		unsigned int projectileDamage = 0;

		unsigned int scoreWhenEquipped = 0;

		Item* requiredParentWhenEquipping = nullptr;
};

#endif