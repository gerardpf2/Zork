#ifndef _Entity_
#define _Entity_

#include <list>
#include <time.h>
#include <vector>

using namespace std;

enum class EntityType
{
	ITEM,
	EXIT,
	ROOM,
	ENEMY,
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

		bool hasChildren() const;

		bool hasChild(const Entity* child, bool recursive = false) const;

		Entity* getChild(const char* name, bool recursive = false) const;

		Entity* getChild(EntityType entityType, const char* name, bool recursive = false) const;

		const list<Entity*>* getAllChildren(EntityType entityType) const;

		void lockItems(bool lock, bool recursive = false) const;

		virtual void update(clock_t msDeltaTime);

		// --- Actions ---

		virtual void look() const;

	protected:

		Entity(const char* name, const char* description, EntityType entityType, Entity* parent);

	private:

		void addChild(Entity* child);

		void removeChild(Entity* child);

	private:

		const char* name = nullptr;

		const char* description = nullptr;

		EntityType entityType;

		Entity* parent = nullptr;

		vector<list<Entity*>> children;
};

#endif