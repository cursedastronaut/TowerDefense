#include "entity_tower.hpp"
#include "../constants.hpp"
#include <string>
#include <math.h>

Turret::Turret() : Entity()
{
}

void Turret::Update(std::vector<Entity*>& EntityList, Game* game)
{
    Shoot(EntityList, game);
}

void Turret::Shoot(const std::vector<Entity*>& EntityList, Game* game)
{
    if (active)
    {
        ImGuiIO *io = &ImGui::GetIO();
        float deltaTime = io->DeltaTime;
        //if no target is initialized, set the closest enemy as the new target.
        if (aimingAt == -1)
        {
            //ImVec2 distanceVec = {0,0};
            float shortestDist = NORMAL_TOWER_RANGE * TILE_SIZE;
                for (size_t o = 0; o < EntityList.size(); o++)
            {
                if (EntityList[o]->GetType() == ENTITYTYPE_ENEMY && EntityList[o]->GetCanStart() == true)
                {
                    // if (sqrtf(powf(EntityList[o]->GetPos().x - pos.x, 2.0f) + powf(EntityList[o]->GetPos().y - pos.y, 2.0f)) < shortestDist)
                    // {
                    //     aimingAt = o;
                    //     shortestDist = sqrtf(powf(EntityList[o]->GetPos().x - pos.x, 2.0f) + powf(EntityList[o]->GetPos().y - pos.y, 2.0f));
                    // }      

                    
                    
                    //distanceVec = EntityList[o]->pos;
                    if (sqrtf(powf(EntityList[o]->pos.x - pos.x, 2.f) + powf(EntityList[o]->pos.y - pos.y, 2.f)) < shortestDist)
                    {
                        aimingAt = o;
                        shortestDist = sqrtf(powf(EntityList[o]->pos.x - pos.x, 2.f) + powf(EntityList[o]->pos.y - pos.y, 2.f));
                        printf("\nshort:%f\n", shortestDist);
                    }        
                }           
            }
        }
        else
        {
            //debug tower aim
            game->AddRectFilledTexlist(500.f + (int)(pos.x / TILE_SIZE), 29,
                {EntityList[aimingAt]->GetPos().x - 16, EntityList[aimingAt]->GetPos().y - 16},
                {EntityList[aimingAt]->GetPos().x + 16, EntityList[aimingAt]->GetPos().y + 16},
                IM_COL32(255, fminf(pos.x / 3, 255), 0, 150)
            );

            if (EntityList[aimingAt]->GetLife() > 0)
            {
                if (cooldown <= 0)
                {
                    if (towerClass == 2)
                        EntityList[aimingAt]->EditSpeed(EntityList[aimingAt]->GetMaxSpeed() / 2.f);
                    //deals a certain amount of damage to the target depending on the turret's level.
                    EntityList[aimingAt]->Damage(shootingStrengh + level, aimingAt);
                    cooldown = maxCooldown - (level / 4);
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
    
}
void Turret::Draw(Game* game, Resources& res, int z) 
{
    if (active)
    {
        ImGui::Text("lvl: %d", level);
        ImVec2 uvUL = {0,0};
        ImVec2 uvBR = {1,1};
        switch (towerClass)
        {
            //default tower
            case NORMAL_ATTACK:
                if (!level)
                {
                    uvUL = {0,0.0f};
                    uvBR = {0.25f,0.25f};
                }
                else
                {
                    uvUL = {0.5f,0.25f};
                    uvBR = {0.75f,0.5f};
                }
                break;
            
            //slow but strong tower
            case SLOW_TOWERCLASS:
                if (!level)
                {
                    uvUL = {0,0.25f};
                    uvBR = {0.25f,0.50f};
                }
                else
                {
                    uvUL = {0.5f,0.5f};
                    uvBR = {0.75f,0.75f};
                }
                break;

            //fast but weak tower
            case FAST_TOWERCLASS:
                if (!level)
                {
                    uvUL = {0.5f,0.0f};
                    uvBR = {0.75f,0.25f};
                }
                else
                {
                    uvUL = {0.0f,0.5f};
                    uvBR = {0.25f,0.75f};
                }
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

bool Turret::Spawn(ImVec2 pos2, Tilemap& tilemap, std::vector<Entity*>& EntityList)
{
    pos2.x = (int)(pos2.x/TILE_SIZE)*TILE_SIZE;
    pos2.y = (int)(pos2.y/TILE_SIZE)*TILE_SIZE;

    if (tilemap.mGrid[(int)(pos2.y/TILE_SIZE * GRID_WIDTH + pos2.x/TILE_SIZE)])
        return 0;

    for (size_t i = 0; i < EntityList.size(); i++)
    {
        if (EntityList[i]->GetPos().x == pos2.x && EntityList[i]->GetPos().y == pos2.y)
        {
            if (EntityList[i]->GetClassType() == GetClassType())
            {
                if (!EntityList[i]->GetLevel())
                {
                    EntityList[i]->EditLevel(1);
                    return 1;
                }
                else
                    return 0;
            }
            else
                return 0;
            
        }
    }
    
    pos       = pos2;
    type      = ENTITYTYPE_TOWER;
    aimingAt  = -1;
    cooldown  = 0;
    level     = 0;
    active    = true;
    return 1;
    
}