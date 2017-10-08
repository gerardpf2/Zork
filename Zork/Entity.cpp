#include "Entity.h"

Entity::Entity(string name, string description, EntityType entityType, Entity* parent) :
	name(name), description(description), entityType(entityType)
{
	updateParent(parent);
}

Entity::~Entity()
{
	for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		if((*it)->getParent() == this) delete *it;

	entities.clear();
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

void Entity::updateParent(Entity* newParent)
{
	if(parent) parent->removeEntity(this);

	parent = newParent;

	if(parent) parent->addEntity(this);
}

void Entity::addEntity(Entity* entity)
{
	entities.push_back(entity);
}

void Entity::removeEntity(Entity* entity)
{
	entities.remove(entity);
}