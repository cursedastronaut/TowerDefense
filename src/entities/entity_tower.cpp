#include "../tilemap.hpp"
#include "../imgui_utils.hpp"
#include "../entity.hpp"
#include "../constants.hpp"
#include <string>

Entity::Turret::Turret()
    : type(0)
{
}

void Entity::drawTower(Game* game, Resources& res)
{
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (turretArray[i].active)
        {
           //turretArray[i].Draw();
            //ImGui::Text("%d", turretArray[i].type);
            ImVec2 uvUL = {0,0};
            ImVec2 uvBR = {1,1};
            switch (turretArray[i].type)
            {
                case 0:
                    uvUL = {0,0.0f};
                    uvBR = {0.25f,0.25f};
                    break;

                default:
                    break;
            }
            game->AddToTexlist(2000+i,
                res.Turret.id,                                                               
                {turretArray[i].pos.x, turretArray[i].pos.y-TILE_SIZE},                                            
                {turretArray[i].pos.x+res.Turret.width/4, turretArray[i].pos.y+res.Turret.height/4-TILE_SIZE},                 
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
        if (!turretArray[i].active)
        {
            turretArray[i].pos       = pos;
            turretArray[i].type      = type;
            turretArray[i].aimingAt  = 0;
            turretArray[i].cooldown  = 0;
            turretArray[i].level     = 0;
            turretArray[i].active    = true;
            return;
        }
    }
}