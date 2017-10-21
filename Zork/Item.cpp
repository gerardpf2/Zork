#include "Item.h"

#include <assert.h>
#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, unsigned int scoreWhenEquipped, bool canBeUsedToAttack, unsigned int attackDamage, unsigned int throwDamage, Item* requiredParentWhenEquipping) :
	Entity(name, description, EntityType::ITEM, parent), canBeEquipped(true), scoreWhenEquipped(scoreWhenEquipped), canBeUsedToAttack(canBeUsedToAttack), attackDamage(attackDamage), throwDamage(throwDamage), requiredParentWhenEquipping(requiredParentWhenEquipping)
{
	assert(parent);
}

Item::~Item()
{ }

bool Item::getCanBeEquipped() const
{
	return canBeEquipped;
}

void Item::setCanBeEquipped(bool canBeEquipped)
{
	this->canBeEquipped = canBeEquipped;
}

bool Item::getCanBeUsedToAttack() const
{
	return canBeUsedToAttack;
}

unsigned int Item::getAttackDamage() const
{
	return attackDamage;
}

unsigned int Item::getThrowDamage() const
{
	return throwDamage;
}

unsigned int Item::getScoreWhenEquipped()
{
	unsigned int score = scoreWhenEquipped;

	scoreWhenEquipped = 0; // Avoid incrementing score multiple times (t, d, t, d, ...)

	return score;
}

Item* Item::getRequiredParentWhenEquipping() const
{
	return requiredParentWhenEquipping;
}

// --- Actions ---

void Item::look() const
{
	cout << getName() << endl;
	cout << getDescription() << endl;

	const list<Entity*>* items = getAllChildren(EntityType::ITEM);

	if(!items->empty())
	{
		cout << "This contains:" << endl;

		for(list<Entity*>::const_iterator it = items->begin(); it != items->end(); ++it)
		{
			cout << "\t" << (*it)->getName();
			if((*it)->hasChildren()) cout << " +";
			cout << endl;
		}
	}
}