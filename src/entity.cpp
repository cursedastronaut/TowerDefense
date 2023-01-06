#include "entity.hpp"
#include "constants.hpp"

Entity::Entity(Tilemap& tilemap)
{
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL /* * level*/); i++)
    {
        for (uint32_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint32_t x = 0; x < GRID_WIDTH; x++)
            {
                enemyArray[i].type = 1;
                if (tilemap.cGrid[y * GRID_WIDTH + x] == 0x06)
                {
                    enemyArray[i].hasSpawned = true;
                    enemyArray[i].pos.x = x * TILE_SIZE;
                    enemyArray[i].pos.y = y * TILE_SIZE;
                }
            }
        }
    }
}

void Entity::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
}

void Entity::Draw(ImDrawList& list, Resources& res)
{
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL /* * level*/); i++)
    {
        if (enemyArray[i].type == 1)
        {
            list.AddImage(
                res.Fighter4.id,                                                               
                {enemyArray[1].pos.x, enemyArray[1].pos.y},                                            
                {enemyArray[1].pos.x+res.Fighter4.width/4, enemyArray[1].pos.y+10+res.Fighter4.height/5},                 
                {0, 0},                           
                {0.25, 0.25}     
            );
            //ImGui::Text("Enemy %d X: %f; Y: %f", i, enemyArray[1].pos.x, enemyArray[1].pos.y);
        }
    }
}