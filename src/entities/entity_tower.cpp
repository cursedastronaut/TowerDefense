//#include "../tilemap.hpp"
//include "../imgui_utils.hpp"
//#include "../entity.hpp"
#include "entity_tower.hpp"
#include "../constants.hpp"
#include <string>
#include <math.h>

/*Turret::Turret()
    //: this->type(0)
{
}*/

void Turret::Shoot()
{/*
    ImGuiIO *io = new ImGuiIO();
    float deltaTime = io->DeltaTime;
    //if no target is initialized, set the closest enemy as the new target.
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (turretArray[i].active)
        {
            if (turretArray[i].aimingAt == -1)
            {
                float shortestDist = INFINITY;
                for (int o = 0; o < ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL); o++)
                {
                    if (enemyArray[o].canStart)
                    {
                        if (sqrtf(powf(enemyArray[o].pos.x - turretArray[i].pos.x, 2.0f) + powf(enemyArray[o].pos.y - turretArray[i].pos.y, 2.0f)) < shortestDist)
                        {
                            turretArray[i].aimingAt = o;
                            shortestDist = sqrtf(powf(enemyArray[o].pos.x - turretArray[i].pos.x, 2.0f) + powf(enemyArray[o].pos.y - turretArray[i].pos.y, 2.0f));
                        }
                    }
                }
            }
            else
            {
                if (enemyArray[turretArray[i].aimingAt].life > 0)
                {
                    if (turretArray[i].cooldown <= 0)
                    {
                            //deals a certain amount of damage to the target depending on the turret's level.
                            switch(turretArray[i].type)
                            {
                                //tower shooting bullets.
                                case 0:
                                enemyArray[turretArray[i].aimingAt].life -= 1 + turretArray[i].level * 2;
                                turretArray[i].cooldown = 2 - (turretArray[i].level / 2);                    
                                break;

                                //tower firing missiles.
                                //TODO: add a function that spawns missiles.
                                case 1:
                                //missile function goes here
                                turretArray[i].cooldown = 5 - turretArray[i].level; 
                                break;
                            }
                    }
                    else
                    {
                        turretArray[i].cooldown -= deltaTime;
                    }
                }
                //once the enemy dies, search for a new target.
                else
                {
                    turretArray[i].aimingAt = -1;
                }
                ImGui::Text("Tower aiming at: %d\nTower doing your mom at: longitude 69 latitude 420\nTower cooldown: %f", turretArray[i].aimingAt, turretArray[i].cooldown);
        }
        
        }
    }
    */
}
void Turret::Draw(Game* game, Resources& res, Tilemap& tilemap)
{/*
    int debug;
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (turretArray[i].active)
        {
            debug++;
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
    ImGui::Text("towers: %d", debug);
    */
}

void Turret::Spawn(ImVec2 pos, int type, Tilemap& tilemap)
{/*
    pos.x = (int)(pos.x/TILE_SIZE)*TILE_SIZE;
    pos.y = (int)(pos.y/TILE_SIZE)*TILE_SIZE;
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (turretArray[i].pos.x == pos.x && turretArray[i].pos.y == pos.y)
            return;
    }
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (!turretArray[i].active)
        {
            if (tilemap.mGrid[(int)(pos.y/32 * GRID_WIDTH + pos.x/32)])
                return;
            
            turretArray[i].pos       = pos;
            turretArray[i].type      = type;
            turretArray[i].aimingAt  = 0;
            turretArray[i].cooldown  = 0;
            turretArray[i].level     = 0;
            turretArray[i].active    = true;
            return;
        }
    }*/
}