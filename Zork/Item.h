#ifndef _Item_
#define _Item_

#include "Entity.h"

class Item : public Entity
{
	public:

		Item(const char* name, const char* description, Entity* parent, unsigned int scoreWhenEquipped, bool canBeUsedToAttack, unsigned int attackDamage, unsigned int throwDamage, Item* requiredParentWhenEquipping = nullptr);

		virtual ~Item();

		bool getCanBeEquipped() const;

		void setCanBeEquipped(bool canBeEquipped);

		bool getCanBeUsedToAttack() const;

		unsigned int getAttackDamage() const;

		unsigned int getThrowDamage() const;

		unsigned int getScoreWhenEquipped();

		Item* getRequiredParentWhenEquipping() const;

		// --- Actions ---

		virtual void look() const override;

	private:

		bool canBeEquipped;

		bool canBeUsedToAttack;

		unsigned int attackDamage;

		unsigned int throwDamage;

		unsigned int scoreWhenEquipped;

		Item* requiredParentWhenEquipping;
};

#endif