#include "entity.hpp"
#include "constants.hpp"

#include <string>

Entity::Entity(Tilemap& tilemap)
{
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL /* * level*/); i++)
    {
        enemyArray[i] = Enemy(tilemap);
    }
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        turretArray[i].type = 0;
    }
}

void Entity::Update(Game* game, Resources& res, Tilemap& tilemap)
{
    Movement(tilemap);
    Draw(game, res);
    if (ImGui::Button("Execute order 66", {100, 50}) == true)
    {
        deathEnemy();
    }
}

void Entity::Draw(Game* game, Resources& res)
{
    drawEnemy(game, res);
    drawTower(game, res);
}

void Entity::Movement(Tilemap& tilemap)
{
    moveEnemy(tilemap);
}