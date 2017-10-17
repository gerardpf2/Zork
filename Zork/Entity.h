#ifndef _Entity_
#define _Entity_

#include <list>
#include <vector>
#include <time.h>

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

		bool hasChild(const Entity* child, bool recursive = false) const;

		Entity* getChild(EntityType entityType, const char* name, bool recursive = false) const;

		const list<Entity*>* getAllChildren(EntityType entityType) const;

		virtual void update(clock_t msDeltaTime);

		// --- Actions ---

		virtual bool look(const vector<string>& tokens) const;

	protected:

		Entity(const char* name, const char* description, EntityType entityType, Entity* parent);

	private:

		void addChild(Entity* child);

		void removeChild(Entity* child);

	private:

		const char* name;

		const char* description;

		EntityType entityType;

		Entity* parent = nullptr;

		vector<list<Entity*>> children;
};

#endif