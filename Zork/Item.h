#ifndef _Item_
#define _Item_

#include "Entity.h"

class Item : public Entity
{
	public:

		Item(string name, string description, Entity* parent);
		virtual ~Item();
};

#endif