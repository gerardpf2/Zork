#include "Item.h"

Item::Item(string name, string description, Entity* parent) :
	Entity(name, description, ITEM, parent)
{

}

Item::~Item()
{

}