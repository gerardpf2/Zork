#include "Entity.h"

#include <iostream>

Entity::Entity(string name, string description, EntityType entityType, Entity* parent) :
	name(name), description(description), entityType(entityType)
{
	entities.resize(5); // EntityType amount

	updateParent(parent);
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

Entity* Entity::getEntity(EntityType entityType, string name)
{
	list<Entity*>* allEntities = getAllEntities(entityType);

	for(list<Entity*>::iterator it = allEntities->begin(); it != allEntities->end(); ++it)
		if((*it)->name == name) return *it;

	return NULL;
}

list<Entity*>* Entity::getAllEntities(EntityType entityType)
{
	return &entities[entityType];
}

void Entity::addEntity(Entity* entity)
{
	entities[entity->getEntityType()].push_back(entity);
}

void Entity::removeEntity(Entity* entity)
{
	entities[entity->getEntityType()].remove(entity);
}

// --- Actions ---

void Entity::look(vector<string>& tokens)
{
	cout << "Entity::look" << endl;
}