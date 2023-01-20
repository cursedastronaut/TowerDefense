#include "entity_tower.hpp"
#include "../constants.hpp"
#include <string>
#include <math.h>
#include "../calc.hpp"
Turret::Turret() : Entity()
{}


void Turret::Update(std::vector<Entity*>& EntityList, Game* game)
{
    Shoot(EntityList, game);
}

//Turret aims at an enemy and shoots it until its dead.
void Turret::Shoot(const std::vector<Entity*>& EntityList, Game* game)
{
    if (active)
    {
        ImGuiIO *io = &ImGui::GetIO();
        float deltaTime = io->DeltaTime;
        //If the tower is not aiming at anyone (aimingAt = -1), find a new enemy to aim.
        //The tower aims the closest enemy within range.
        if (aimingAt == -1)
        {
            //Range definition
            float currentDist = 0;
            float shortestDist = NORMAL_TOWER_RANGE * TILE_SIZE;
            //Looping through all entities
            for (size_t o = 0; o < EntityList.size(); o++)
            {
                //If entity is an enemy and is active (just in case)
                if (EntityList[o]->GetType() == ENTITYTYPE_ENEMY && EntityList[o]->GetCanStart() == true)
                {
                    //Checks if the distance with the enemy we are looking at is lower than the last one registered.
                    //First one registered is the range.
                    currentDist = sqrtf(powf(EntityList[o]->pos.x - pos.x, 2.f) + powf(EntityList[o]->pos.y - pos.y, 2.f));
                    if (currentDist < shortestDist)
                    {
                        //Aims at that enemy. Will be overwritten if other enemies are closer until it found the closest.
                        aimingAt = o;
                        shortestDist = sqrtf(powf(EntityList[o]->pos.x - pos.x, 2.f) + powf(EntityList[o]->pos.y - pos.y, 2.f));
                    }        
                }           
            }
        }
        //Tower is actually aiming at an enemy, so we shoot it.
        else
        {
            //If the enemy is still alive and the cooldown is above zero
            if (EntityList[aimingAt]->GetLife() > 0)
            {
                if (cooldown <= 0)
                {
                    //If this is a fast tower, it will slow down the enemy.
                    if (towerClass == FAST_TOWERCLASS)
                        EntityList[aimingAt]->EditSpeed(EntityList[aimingAt]->GetMaxSpeed() / 2.f);
                    //Deals a certain amount of damage to the target depending on the turret's level.
                    EntityList[aimingAt]->Damage(shootingStrengh + level, aimingAt);
                    //Sets the cooldown back to its maximum. It is lower when leveled up.
                    cooldown = maxCooldown - (level / 4);
                }
                else
                {
                    //Lowers the cooldown
                    cooldown -= deltaTime;
                }
            }
            //once the enemy dies, search for a new target.
            else
            {
                aimingAt = -1;
            }
        }
    }
    
}

//Draws the turret.
void Turret::Draw(Game* game, Resources& res, int z) 
{
    if (active)
    {
        ImVec2 uvUL = {0,0};
        ImVec2 uvBR = {1,1};
        //Chooses the UV on the towers texture depending of what kind of tower it is.
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

        //Actual drawing of the tower
        game->AddToTexlist(z, 10,
            res.Turret.id,                                                               
            {pos.x, pos.y-TILE_SIZE},                                            
            {pos.x+res.Turret.width/4, pos.y+res.Turret.height/4-TILE_SIZE},                 
            uvUL,                           
            uvBR     
        );        
    }
}

//Spawning values.
bool Turret::Spawn(ImVec2 pos2, Tilemap& tilemap, std::vector<Entity*>& EntityList)
{
    pos2 = Calc::ToWorldInt(pos2);

    //If the tile you want to spawn the turret on is not grass, we won't activate it and return 0.
    //Returning 0 means the game won't remove the money. For the player, the tower didn't spawn.
    if (tilemap.mGrid[(int)(pos2.y/TILE_SIZE * GRID_WIDTH + pos2.x/TILE_SIZE)])
        return 0;

    //Looping through every entity.
    for (size_t i = 0; i < EntityList.size(); i++)
    {
        //If another entity is at the same place (Since you cannot spawn turrets where enemies can walk, it checks if it is on another turret)
        if (EntityList[i]->GetPos().x == pos2.x && EntityList[i]->GetPos().y == pos2.y)
        {
            //If the turret who is already there is the same kind as the one the player is trying to spawn
            if (EntityList[i]->GetClassType() == GetClassType())
            {
                //If the turret who's already there has not leveled up yet, level it up!
                //If it already has, return 0
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
    
    //The player placed the turret at a correct place, the default values are set.
    pos       = pos2;
    type      = ENTITYTYPE_TOWER;
    aimingAt  = -1;
    cooldown  = 0;
    level     = 0;
    active    = true;
    return 1;
    
}