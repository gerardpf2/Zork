#ifndef _Item_
#define _Item_

#include "Entity.h"

class Item : public Entity
{
	public:

		Item(const char* name, const char* description, Entity* const parent);

		virtual ~Item();
};

#endif