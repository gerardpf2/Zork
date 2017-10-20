#ifndef _Item_
#define _Item_

#include "Entity.h"

class Item : public Entity
{
	public:

		Item(const char* name, const char* description, Entity* parent, Item* requiredParentWhenEquipping = nullptr);

		virtual ~Item();

		bool getCanBeEquipped() const;

		void setCanBeEquipped(bool canBeEquipped);

		Item* getRequiredParentWhenEquipping() const;

		// --- Actions ---

		virtual void look() const override;

	private:

		bool canBeEquipped;

		Item* requiredParentWhenEquipping;
};

#endif