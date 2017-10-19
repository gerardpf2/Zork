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

	printChildren("This contains:", EntityType::ITEM);
}