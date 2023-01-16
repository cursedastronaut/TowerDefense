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

void Turret::Update(const std::vector<Entity*>& EntityList, Game* game)
{
    Shoot(EntityList, game);
}

void Turret::Shoot(const std::vector<Entity*>& EntityList, Game* game)
{
    ImGuiIO *io = &ImGui::GetIO();
    float deltaTime = io->DeltaTime;
    //if no target is initialized, set the closest enemy as the new target.
    if (aimingAt == -1)
    {
        float shortestDist = 10000;
        for (size_t o = 0; o < EntityList.size(); o++)
        {
            if (EntityList[o]->GetType() == 1 && EntityList[o]->GetCanStart() == true)
            {
                if (sqrtf(powf(EntityList[o]->GetPos().x - pos.x, 2.0f) + powf(EntityList[o]->GetPos().y - pos.y, 2.0f)) < shortestDist)
                {
                    aimingAt = o;
                    shortestDist = sqrtf(powf(EntityList[o]->GetPos().x - pos.x, 2.0f) + powf(EntityList[o]->GetPos().y - pos.y, 2.0f));
                }              
            }           
        }
    }
    else
    {
        if (EntityList[aimingAt]->GetLife() > 0)
        {
            if (cooldown <= 0)
            {
                    //deals a certain amount of damage to the target depending on the turret's level.
                    switch(type)
                    {
                        //tower shooting bullets.
                        case 0:
                        EntityList[aimingAt]->Damage(5 + level, aimingAt);
                        cooldown = 2 - (level / 2);                    
                        break;

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
    }
    ImGui::Text("Tower aiming at: %d\nTower cooldown: %f", aimingAt, cooldown);
}
void Turret::Draw(Game* game, Resources& res, int z) 
{
    if (active)
    {
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
        game->AddToTexlist(z, 10,
            res.Turret.id,                                                               
            {pos.x, pos.y-TILE_SIZE},                                            
            {pos.x+res.Turret.width/4, pos.y+res.Turret.height/4-TILE_SIZE},                 
            uvUL,                           
            uvBR     
        ); 
        
    }
}

void Turret::Spawn(ImVec2 pos2, int type2, Tilemap& tilemap)
{
    pos2.x = (int)(pos2.x/TILE_SIZE)*TILE_SIZE;
    pos2.y = (int)(pos2.y/TILE_SIZE)*TILE_SIZE;

    if (!active)
    {
        if (tilemap.mGrid[(int)(pos2.y/32 * GRID_WIDTH + pos2.x/32)])
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