#include "../tilemap.hpp"
#include "../imgui_utils.hpp"
#include "../entity.hpp"
#include "../constants.hpp"
#include <string>

Entity::Tower::Tower()
    : type(0)
{
}

void Entity::drawTower(ImDrawList& list, Resources& res)
{
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (towerArray[i].active)
        {
           //towerArray[i].Draw();
            //ImGui::Text("%d", towerArray[i].type);
            ImVec2 uvUL = {0,0};
            ImVec2 uvBR = {1,1};
            switch (towerArray[i].type)
            {
                case 0:
                    uvUL = {0,0.0f};
                    uvBR = {0.25f,0.25f};
                    break;

                default:
                    break;
            }
            list.AddImage(
                res.Tower.id,                                                               
                {towerArray[i].pos.x, towerArray[i].pos.y-TILE_SIZE},                                            
                {towerArray[i].pos.x+res.Tower.width/4, towerArray[i].pos.y+res.Tower.height/4-TILE_SIZE},                 
                uvUL,                           
                uvBR     
            ); 
            
        }
    }
    
    
}

void Entity::spawnTower(ImVec2 pos, int type)
{
    pos.x = (int)(pos.x/TILE_SIZE)*TILE_SIZE;
    pos.y = (int)(pos.y/TILE_SIZE)*TILE_SIZE;
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (!towerArray[i].active)
        {
            towerArray[i].pos       = pos;
            towerArray[i].type      = type;
            towerArray[i].aimingAt  = 0;
            towerArray[i].cooldown  = 0;
            towerArray[i].level     = 0;
            towerArray[i].active    = true;
            return;
        }
    }
}