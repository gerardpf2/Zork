#include "Item.h"

#include <assert.h>
#include <iostream>

Item::Item(const char* name, const char* description, Entity* parent, unsigned int scoreWhenEquipped, unsigned int attackDamage, unsigned int projectileDamage, unsigned int healAmount, Item* requiredParentWhenEquipping) :
	Entity(name, description, EntityType::ITEM, parent), scoreWhenEquipped(scoreWhenEquipped), attackDamage(attackDamage), projectileDamage(projectileDamage), healAmount(healAmount), requiredParentWhenEquipping(requiredParentWhenEquipping)
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
	return attackDamage > 0;
}

unsigned int Item::getAttackDamage() const
{
	return attackDamage;
}

unsigned int Item::getProjectileDamage() const
{
	return projectileDamage;
}

bool Item::getCanBeUsedToHeal() const
{
	return healAmount > 0;
}

unsigned int Item::getHealAmount() const
{
	return healAmount;
}

void Item::removeHealAmount()
{
	healAmount = 0;
}

unsigned int Item::getScoreWhenEquipped() const
{
	return scoreWhenEquipped;
}

void Item::removeScoreWhenEquipped()
{
	scoreWhenEquipped = 0;
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