#include "Item.h"

#include <assert.h>
#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, Item* requiredParentWhenEquipping) :
	Entity(name, description, EntityType::ITEM, parent), requiredParentWhenEquipping(requiredParentWhenEquipping)
{
	assert(parent);

	canBeEquipped = !hasAliveEnemyParent(true);
}

Item::~Item()
{ }

bool Item::getCanBeEquipped() const
{
	return canBeEquipped;
}

void Item::setCanBeEquipped(bool canBeEquipped)
{
	this->canBeEquipped = canBeEquipped;
}

Item* Item::getRequiredParentWhenEquipping() const
{
	return requiredParentWhenEquipping;
}

// --- Actions ---

void Item::look() const
{
	cout << getName() << endl;
	cout << getDescription() << endl;

	const list<Entity*>* items = getAllChildren(EntityType::ITEM);

	if(!items->empty())
	{
		cout << "This contains:" << endl;

		for(list<Entity*>::const_iterator it = items->begin(); it != items->end(); ++it)
		{
			cout << "\t" << (*it)->getName();
			if((*it)->hasChildren()) cout << " +";
			cout << endl;
		}
	}
}