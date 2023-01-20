#include "entity.hpp"
#include "constants.hpp"
#include "game.hpp"

#include <string>

Entity::Entity()
{}

Entity::~Entity()
{
}

void Entity::Draw(Game* game, Resources& res, int z)
{
}

bool Entity::Spawn(ImVec2 pos, Tilemap& tilemap)
{return 0;}

void Entity::Movement(Tilemap& tilemap)
{
}