#include "Item.h"

Item::Item(const char* name, const char* description, Entity* parent) :
	Entity(name, description, EntityType::ITEM, parent)
{ }

Item::~Item()
{ }