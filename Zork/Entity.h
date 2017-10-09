#ifndef _Entity_
#define _Entity_

#include <list>
#include <vector>
#include <string>

using namespace std;

enum EntityType
{
	NPC,
	ITEM,
	EXIT,
	ROOM,
	PLAYER,
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

		void updateParent(Entity* newParent);

		Entity* getEntity(EntityType entityType, string name);

		list<Entity*>* getAllEntities(EntityType entityType);

		void addEntity(Entity* entity);

		// --- Actions ---

		virtual void look(vector<string>& tokens);

	private:

		string name;
		string description;
		EntityType entityType;
		Entity* parent;

		vector<list<Entity*>> entities;

		void removeEntity(Entity* entity);
};

#endif