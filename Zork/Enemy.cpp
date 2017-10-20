#include "Enemy.h"

Enemy::Enemy(const char* name, const char* description, Room* room, int health) :
	Creature(name, description, EntityType::ENEMY, room, health)
{ }

Enemy::~Enemy()
{ }