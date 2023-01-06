#include "entity.hpp"
#include "constants.hpp"

#include <string>

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
                    enemyArray[i].pos.x = x * TILE_SIZE;
                    enemyArray[i].pos.y = (y-1) * TILE_SIZE;
                }
            }
        }
    }
}

void Entity::Update(ImDrawList& list, Resources& res, Tilemap& tilemap)
{
    Movement(tilemap);
    Draw(list, res);
}

void Entity::Draw(ImDrawList& list, Resources& res)
{
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL /* * level*/); i++)
    {
        ImVec2 uvUL = {0,0};
        ImVec2 uvBR = {1,1};
        switch (enemyArray[i].direction)
        {
        case 0:
            uvUL = {0,0.75f};
            uvBR = {0.25f,1};
            break;
        
        case 90:
            uvUL = {0,0.50f};
            uvBR = {0.25f,0.75};
            break;

        case 180:
            uvUL = {0,0.0f};
            uvBR = {0.25f,0.25f};
            break;
        case 270:
            uvUL = {0,0.25f};
            uvBR = {0.25f,0.50f};
            break;

        default:
            break;
        }
        list.AddImage(
            res.Fighter4.id,                                                               
            {enemyArray[i].pos.x, enemyArray[i].pos.y},                                            
            {enemyArray[i].pos.x+res.Fighter4.width/4, enemyArray[i].pos.y+res.Fighter4.height/4},                 
            uvUL,                           
            uvBR     
        );
    }
}

void Entity::Movement(Tilemap& tilemap)
{
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
    {
        if (ImGui::Button(std::string("Enemy Start").append(std::to_string(i)).c_str())) {
            enemyArray[i].canStart = true;
        }
        ImGui::Text("%d", enemyArray[i].canStart);
        if (!enemyArray[i].canStart)
            return;

        for (uint32_t y = 0; y < GRID_HEIGHT; y++)
        {
            for (uint32_t x = 0; x < GRID_WIDTH; x++)
            {
                //Handling directions
                switch (tilemap.cGrid[(int)(enemyArray[i].pos.y+TILE_SIZE) / TILE_SIZE * GRID_WIDTH + (int)enemyArray[i].pos.x / TILE_SIZE])
                {
                    case 0x00:
                        break;
                    case 0x02:
                        enemyArray[i].direction = 0;
                        break;
                    case 0x03:
                        enemyArray[i].direction = 90;
                        break;
                    case 0x04:
                        enemyArray[i].direction = 180;
                        break;
                    case 0x05:
                        enemyArray[i].direction = 270;
                        break;
                    
                    default:
                        break;
                }
                //Moves the player
                switch (enemyArray[i].direction)
                {
                    case 180:
                        enemyArray[i].pos.y +=0.25f/60.f;
                        break;
                    case 90:
                        enemyArray[i].pos.x +=0.25f/60.f;
                        break;
                    case 0:
                        enemyArray[i].pos.y -=0.25f/60.f;
                        break;
                    case 270:
                        enemyArray[i].pos.x -=0.25f/60.f;
                        break;
                    
                    default:
                        break;
                }
            } //End of for x
        }    //End of for y
    }
}