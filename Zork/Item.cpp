#include "Item.h"

Item::Item(const char* name, const char* description, Entity* const parent) :
	Entity(name, description, EntityType::ITEM, parent)
{ }

Item::~Item()
{ }