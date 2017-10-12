#ifndef _Entity_
#define _Entity_

#include <list>
#include <vector>

using namespace std;

enum class EntityType
{
	NPC,
	ITEM,
	EXIT,
	ROOM,
	PLAYER,
};

class Entity
{
	public:

		virtual ~Entity();

		const char* getName() const;

		const char* getDescription() const;

		EntityType getEntityType() const;

		const Entity* getParent() const;

		void assignNewParent(Entity* newParent);

		const Entity* getEntity(EntityType entityType, const char* name) const;

		const list<Entity*>* getAllEntities(EntityType entityType) const;

		void addEntity(Entity* entity);

		void update();

		// --- Actions ---

		virtual bool look(const vector<string>& tokens) const;

	protected:

		Entity(const char* name, const char* description, EntityType entityType, Entity* parent);

		virtual void onUpdate();

	private:

		void removeEntity(Entity* entity);

	private:

		const char* name;

		const char* description;

		EntityType entityType;

		Entity* parent = nullptr;

		vector<list<Entity*>> entities;
};

#endif