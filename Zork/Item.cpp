#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent, Item* requiredParentWhenEquipping) :
	Entity(name, description, EntityType::ITEM, parent), requiredParentWhenEquipping(requiredParentWhenEquipping)
{ }

Item::~Item()
{ }

Item* Item::getRequiredParentWhenEquipping() const
{
	return requiredParentWhenEquipping;
}