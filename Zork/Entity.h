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
	protected:

		Entity(const char* name, const char* description, EntityType entityType, Entity* const parent);

		virtual void onUpdate();

	public:

		virtual ~Entity();

		const char* getName() const;

		const char* getDescription() const;

		EntityType getEntityType() const;

		Entity* getParent() const;

		void assignNewParent(Entity* const newParent);

		Entity* getEntity(EntityType entityType, const char* name) const;

		const list<Entity*>* getAllEntities(EntityType entityType) const;

		void addEntity(Entity* const entity);

		void update();

		// --- Actions ---

		virtual bool look(const vector<string>& tokens) const;

	private:

		const char* name;

		const char* description;

		EntityType entityType;

		Entity* parent = nullptr;

		vector<list<Entity*>> entities;

	private:

		void removeEntity(Entity* const entity);
};

#endif