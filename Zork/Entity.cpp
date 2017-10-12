#include "Entity.h"

#include <assert.h>

Entity::Entity(const char* name, const char* description, EntityType entityType, Entity* parent) :
	name(name), description(description), entityType(entityType)
{
	entities.resize(5); // 5 different entity types

	assignNewParent(parent);
}

Entity::~Entity()
{
	for(unsigned int i = 0; i < entities.size(); ++i)
	{
		for(list<Entity*>::iterator it = entities[i].begin(); it != entities[i].end(); ++it)
			delete *it;

		entities[i].clear();
	}

	entities.clear();
}

const char* Entity::getName() const
{
	return name;
}

const char* Entity::getDescription() const
{
	return description;
}

EntityType Entity::getEntityType() const
{
	return entityType;
}

const Entity* Entity::getParent() const
{
	return parent;
}

void Entity::assignNewParent(Entity* newParent)
{
	if(parent) parent->removeEntity(this);

	parent = newParent;

	if(parent) parent->addEntity(this);
}

const Entity* Entity::getEntity(EntityType entityType, const char* name) const
{
	const list<Entity*>* allEntities = getAllEntities(entityType);

	for(list<Entity*>::const_iterator it = allEntities->begin(); it != allEntities->end(); ++it)
		if((*it)->name == name) return *it;

	return nullptr;
}

const list<Entity*>* Entity::getAllEntities(EntityType entityType) const
{
	assert((unsigned int)entityType < entities.size());

	return &entities[(unsigned int)entityType];
}

void Entity::addEntity(Entity* entity)
{
	assert((unsigned int)entity->getEntityType() < entities.size());

	entities[(unsigned int)entity->getEntityType()].push_back(entity);
}

void Entity::removeEntity(Entity* entity)
{
	assert((unsigned int)entity->getEntityType() < entities.size());

	entities[(unsigned int)entity->getEntityType()].remove(entity);
}

void Entity::update()
{
	onUpdate();

	for(unsigned int i = 0; i < entities.size(); ++i)
	{
		for(list<Entity*>::iterator it = entities[i].begin(); it != entities[i].end(); ++it)
			if(*it) (*it)->update();
	}
}

void Entity::onUpdate()
{ }

// --- Actions ---

#include <iostream>

bool Entity::look(const vector<string>& tokens) const
{
	cout << "Entity::look" << endl;

	return true;
}