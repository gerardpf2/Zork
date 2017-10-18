#include "Item.h"

#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, Item* requiredParentWhenEquipping) :
	Entity(name, description, EntityType::ITEM, parent), requiredParentWhenEquipping(requiredParentWhenEquipping)
{ }

Item::~Item()
{ }

Item* Item::getRequiredParentWhenEquipping() const
{
	return requiredParentWhenEquipping;
}

// --- Actions ---

void Item::look() const
{
	cout << getName() << endl;
	cout << getDescription() << endl;

	const list<Entity*>* children = getAllChildren(EntityType::ITEM);

	if(!children->empty())
	{
		cout << "It contains" << endl;

		for(list<Entity*>::const_iterator it = children->begin(); it != children->end(); ++it)
			cout << "   " << (*it)->getName() << endl;
	}
}