#include "Entity.h"

#include "Enemy.h"
#include <assert.h>
#include <iostream>

Entity::Entity(const char* name, const char* description, EntityType entityType, Entity* parent) :
	name(name), description(description), entityType(entityType)
{
	assert(name);
	assert(description);

	children.resize(5); // 5 different entity types

	assignNewParent(parent);
}

Entity::~Entity()
{
	for(unsigned int i = 0; i < children.size(); ++i)
		children[i].clear();

	children.clear();
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
	if(parent) parent->removeChild(this);

	parent = newParent;

	if(parent) parent->addChild(this);
}

bool Entity::hasChildren() const
{
	for(unsigned int i = 0; i < children.size(); ++i)
		if(!children[i].empty()) return true;

	return false;
}

bool Entity::hasChild(const Entity* child, bool recursive) const
{
	assert(child);

	return getChild(child->getEntityType(), child->getName(), recursive) != nullptr;
}

Entity* Entity::getChild(const char* name, bool recursive) const
{
	assert(name);

	for(unsigned int i = 0; i < children.size(); ++i)
		for(list<Entity*>::const_iterator it = children[i].begin(); it != children[i].end(); ++it)
			if(strcmp((*it)->getName(), name) == 0) return *it;

	if(recursive)
	{
		for(unsigned int i = 0; i < children.size(); ++i)
			for(list<Entity*>::const_iterator it = children[i].begin(); it != children[i].end(); ++it)
			{
				Entity* child = (*it)->getChild(name, recursive);
				if(child) return child;
			}
	}

	return nullptr;
}

Entity* Entity::getChild(EntityType entityType, const char* name, bool recursive) const
{
	assert(name);

	const list<Entity*>* allEntities = getAllChildren(entityType);

	for(list<Entity*>::const_iterator it = allEntities->begin(); it != allEntities->end(); ++it)
		if(strcmp((*it)->getName(), name) == 0) return *it;

	if(recursive)
	{
		for(unsigned int i = 0; i < children.size(); ++i)
			for(list<Entity*>::const_iterator it = children[i].begin(); it != children[i].end(); ++it)
			{
				Entity* child = (*it)->getChild(entityType, name, recursive);
				if(child) return child;
			}
	}

	return nullptr;
}

const list<Entity*>* Entity::getAllChildren(EntityType entityType) const
{
	assert((unsigned int)entityType < children.size());

	return &children[(unsigned int)entityType];
}

bool Entity::hasAliveEnemyParent(bool recursive) const
{
	if(parent)
	{
		if(parent->entityType == EntityType::ENEMY)
			return ((Enemy*)parent)->isAlive();
		if(recursive) return parent->hasAliveEnemyParent(recursive);
	}

	return false;
}

void Entity::addChild(Entity* child)
{
	assert(child);
	assert((unsigned int)child->getEntityType() < children.size());

	children[(unsigned int)child->getEntityType()].push_back(child);
}

void Entity::removeChild(Entity* child)
{
	assert(child);
	assert((unsigned int)child->getEntityType() < children.size());

	children[(unsigned int)child->getEntityType()].remove(child);
}

void Entity::update(clock_t msDeltaTime)
{ }

// --- Actions ---

void Entity::look() const
{
	cout << name << endl;
	cout << description << endl;
}