#include "Room.h"

Room::Room(const char* name, const char* description) :
	Entity(name, description, EntityType::ROOM, nullptr)
{ }

Room::~Room()
{ }