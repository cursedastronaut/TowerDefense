//#include "../tilemap.hpp"
//include "../imgui_utils.hpp"
//#include "../entity.hpp"
#include "entity_tower.hpp"
#include "../constants.hpp"
#include <string>
#include <math.h>

Turret::Turret() : Entity()
{
}

void Turret::Shoot()
{/*
    ImGuiIO *io = new ImGuiIO();
    float deltaTime = io->DeltaTime;
    //if no target is initialized, set the closest enemy as the new target.
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (active)
        {
            if (aimingAt == -1)
            {
                float shortestDist = INFINITY;
                for (int o = 0; o < ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL); o++)
                {
                    if (enemyArray[o].canStart)
                    {
                        if (sqrtf(powf(enemyArray[o].pos.x - pos.x, 2.0f) + powf(enemyArray[o].pos.y - pos.y, 2.0f)) < shortestDist)
                        {
                            aimingAt = o;
                            shortestDist = sqrtf(powf(enemyArray[o].pos.x - pos.x, 2.0f) + powf(enemyArray[o].pos.y - pos.y, 2.0f));
                        }
                    }
                }
            }
            else
            {
                if (enemyArray[aimingAt].life > 0)
                {
                    if (cooldown <= 0)
                    {
                            //deals a certain amount of damage to the target depending on the turret's level.
                            switch(type)
                            {
                                //tower shooting bullets.
                                case 0:
                                enemyArray[aimingAt].life -= 1 + level * 2;
                                cooldown = 2 - (level / 2);                    
                                break;

                                //tower firing missiles.
                                //TODO: add a function that spawns missiles.
                                case 1:
                                //missile function goes here
                                cooldown = 5 - level; 
                                break;
                            }
                    }
                    else
                    {
                        cooldown -= deltaTime;
                    }
                }
                //once the enemy dies, search for a new target.
                else
                {
                    aimingAt = -1;
                }
                ImGui::Text("Tower aiming at: %d\nTower doing your mom at: longitude 69 latitude 420\nTower cooldown: %f", aimingAt, cooldown);
        }
        
        }
    }
    */
}
void Turret::Draw(Game* game, Resources& res) 
{
    int debug;
    if (active)
    {
        debug++;
        //Draw();
        //ImGui::Text("%d", type);
        ImVec2 uvUL = {0,0};
        ImVec2 uvBR = {1,1};
        switch (type)
        {
            case 0:
                uvUL = {0,0.0f};
                uvBR = {0.25f,0.25f};
                break;

            default:
                break;
        }
        game->AddToTexlist(2000,
            res.Turret.id,                                                               
            {pos.x, pos.y-TILE_SIZE},                                            
            {pos.x+res.Turret.width/4, pos.y+res.Turret.height/4-TILE_SIZE},                 
            uvUL,                           
            uvBR     
        ); 
        
    }
ImGui::Text("towers: %d", debug);
}

void Turret::Spawn(ImVec2 pos2, int type2, Tilemap& tilemap)
{
    pos2.x = (int)(pos2.x/TILE_SIZE)*TILE_SIZE;
    pos2.y = (int)(pos2.y/TILE_SIZE)*TILE_SIZE;

    if (!active)
    {
        if (tilemap.mGrid[(int)(pos.y/32 * GRID_WIDTH + pos.x/32)])
            return;
        
        pos       = pos2;
        type      = type2;
        aimingAt  = 0;
        cooldown  = 0;
        level     = 0;
        active    = true;
        return;
    }
    
}