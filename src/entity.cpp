#include "entity.hpp"
#include "constants.hpp"

#include <string>

Entity::Entity(Tilemap& tilemap)
{
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL /* * level*/); i++)
    {
        enemyArray[i] = Enemy(tilemap);
    }
    
    static int test = 0;
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        towerArray[i].type = 0;
    }
}

void Entity::Update(ImDrawList& list, Resources& res, Tilemap& tilemap)
{
    Movement(tilemap);
    Draw(list, res);
}

void Entity::Draw(ImDrawList& list, Resources& res)
{
    drawEnemy(list, res);
    drawTower(list, res);
}

void Entity::Movement(Tilemap& tilemap)
{
    moveEnemy(tilemap);
}