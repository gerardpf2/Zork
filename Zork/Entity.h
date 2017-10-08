#ifndef _Entity_
#define _Entity_

#include <list>
#include <string>

using namespace std;

enum EntityType
{
	ITEM,
	EXIT,
	ROOM,
	PLAYER,
	CREATURE,
};

class Entity
{
	protected:

		Entity(string name, string description, EntityType entityType, Entity* parent);

	public:

		virtual ~Entity();

		string getName();

		string getDescription();

		EntityType getEntityType();

		Entity* getParent();

		void addEntity(Entity* entity);

	private:

		string name;
		string description;
		EntityType entityType;
		Entity* parent;

		list<Entity*> entities;
};

#endif