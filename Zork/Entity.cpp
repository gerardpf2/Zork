#include "Entity.h"

Entity::Entity(string name, string description, EntityType entityType, Entity* parent) :
	name(name), description(description), entityType(entityType), parent(parent)
{
	if(parent) parent->addEntity(this);
}

Entity::~Entity()
{

}

string Entity::getName()
{
	return name;
}

string Entity::getDescription()
{
	return description;
}

EntityType Entity::getEntityType()
{
	return entityType;
}

Entity* Entity::getParent()
{
	return parent;
}

void Entity::addEntity(Entity* entity)
{
	entities.push_back(entity);
}