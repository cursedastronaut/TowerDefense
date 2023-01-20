#include "../tilemap.hpp"
#include "../imgui_utils.hpp"
#include "../constants.hpp"
#include "entity_enemy.hpp"
#include <string>
#include <math.h>

Enemy::Enemy()
{
    
}
//Played at enemy spawn
Enemy::Enemy(Tilemap& tilemap)
    : direction(0)
{
    //Looping through all the path tiles tiles
    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            type = 1;
            //Finds the Spawn tile, and sets enemy position to this tile.
            if (tilemap.cGrid[y * GRID_WIDTH + x] == 0x06)
            {
                pos.x = x * TILE_SIZE + (TILE_SIZE / 2);
                pos.y = y * TILE_SIZE + (TILE_SIZE / 2);
            }
        }
    }
    life        = WIMP_LIFE;
}

void Enemy::Update(std::vector<Entity*>& EntityList, Game* game)
{
    //If enemy updating is a healer
    if (GetClassType() == ENEMYTYPE_HEALER)
    {

        if (cooldown <= 0)
        {
            //Finds the closest enemy and heals it.
            ImVec2 distanceVec = {0,0};
            float shortestDistance = 999;
            size_t closestEnemy = 0;
            for (size_t i = 0; i < EntityList.size(); i++)
            {
                if (EntityList[i]->GetType() == ENTITYTYPE_ENEMY && EntityList[i]->GetCanStart() == true)
                {
                    distanceVec = EntityList[i]->GetPos();
                    if (sqrtf(powf(EntityList[i]->pos.x - pos.x, 2.f) + powf(EntityList[i]->pos.y - pos.y, 2.f)) < shortestDistance
                        && (EntityList[i] != this))
                    {
                        closestEnemy = i;
                        shortestDistance = sqrtf(pow(EntityList[i]->pos.x - pos.x, 2) + pow(EntityList[i]->pos.y - pos.y, 2));
                    }
                }
            }
            EntityList[closestEnemy]->life += HEAL;
            cooldown = HEALER_COOLDOWN;
        }
        else
        {
            cooldown -= ImGui::GetIO().DeltaTime;
        }
    }
}

void Enemy::Draw(Game* game, Resources& res, int z)
{
    //If enemy is dead but somehow still active, discard the following.
    if (life <= 0)
    {
        return;
    }

    //Sets default textures
    Texture texture[2] = {res.Fighter4, res.Fighter4Frozen};

    ImVec2 uvUL = {0,0};
    ImVec2 uvBR = {1,1};
    //Changes UV based on the direction the enemy is walking towards
    switch (direction)
    {
    case 90:
        uvUL = {0,0.75f};
        uvBR = {0.25f,1};
        break;
    
    case 00:
        uvUL = {0,0.50f};
        uvBR = {0.25f,0.75};
        break;

    case 270:
        uvUL = {0,0.0f};
        uvBR = {0.25f,0.25f};
        break;
    case 180:
        uvUL = {0,0.25f};
        uvBR = {0.25f,0.50f};
        break;

    default:
        break;
    }

    //Sets the textures for the enemy, depending of its type
    switch (enemyType)
    {
    case ENEMYTYPE_WIMP:
        texture[0] = res.Fighter3;
        texture[1] = res.Fighter3Frozen;
        break;
    
    case ENEMYTYPE_BEEFY:
        texture[0] = res.Fighter4;
        texture[1] = res.Fighter4Frozen;
        break;

    case ENEMYTYPE_HEALER:
        texture[0] = res.Fighter5;
        texture[1] = res.Fighter5Frozen;
        break;
    
    default:
        break;
    }
    //Checks if enemy is slower, if yes, it will draw the frozen texture.
    bool isFrozen = false;
    if (maxSpeed != speed)
        isFrozen = true;
    
    //Changes UV depending on the position, this is where the walking animation is made.
    if (((int)(pos.x/TILE_SIZE) % 2 && (direction == 0 || direction == 180)) || ((int)(pos.y/TILE_SIZE) % 2 && (direction == 90 || direction == 270)))
    {
        uvUL.x += 0.25f;    uvBR.x += 0.25f;
    }
    if (((int)(pos.x/TILE_SIZE) % 4 && (direction == 0 || direction == 180)) || ((int)(pos.y/TILE_SIZE) % 4 && (direction == 90 || direction == 270)))
    {
        uvUL.x += 0.50f;    uvBR.x += 0.50f;
    }
    
    //Actual enemy drawing
    game->AddToTexlist(z, 10,
        texture[isFrozen].id,                                                               
        {pos.x - texture[isFrozen].width / 8, pos.y - texture[isFrozen].height / 8 - texture[isFrozen].height / 8},  
        {pos.x + texture[isFrozen].width / 8, pos.y + texture[isFrozen].height / 8 - texture[isFrozen].height / 8},           
        uvUL,                           
        uvBR     
    );

    //Draws the number of HP of an enemy
    std::string life_count = "HP = ";
    life_count += std::to_string(GetLife());
    game->AddTextTexlist(z,11, 
    {pos.x - texture[isFrozen].width / 8, pos.y}
    , 0xFFFF0000, life_count);

}

void Enemy::Movement(Tilemap& tilemap)
{
    ImGuiIO* io = &ImGui::GetIO();
    float deltaTime = io->DeltaTime;

    //If enemy is dead but somehow still active, discard the following.
    if (life <= 0)
        return;

    //Looping through every path tile
    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            //Handling directions
            if (tilemap.cGrid[(int)(pos.y / TILE_SIZE) * GRID_WIDTH + (int)(pos.x / TILE_SIZE)] != 0x01)
            {
                turnCooldown -= deltaTime;
                if (turnCooldown <= 0)
                {
                    //If the enemy steps on a direction changing tile, it will then change directions.
                    switch (tilemap.cGrid[(int)(pos.y / TILE_SIZE) * GRID_WIDTH + (int)(pos.x / TILE_SIZE)])
                    {
                        case 0x02:
                            direction = 90;
                            break;
                        case 0x03:
                            direction = 0;
                            break;
                        case 0x04:
                            direction = 270;
                            break;
                        case 0x05:
                            direction = 180;
                            break;
                        
                        default:
                            break;
                    }
                    turnCooldown = (TILE_SIZE / 2) / speed;
                }                   
            }
            else
            {
                turnCooldown = (TILE_SIZE / 2) / speed;
            }

            //Moves the player
            switch (direction)
            {
                case 270:
                    pos.y += speed * deltaTime;
                    break;
                case 00:
                    pos.x += speed * deltaTime;
                    break;
                case 90:
                    pos.y -= speed * deltaTime;
                    break;
                case 180:
                    pos.x -= speed * deltaTime;
                    break;
                
                default:
                    break;
            }
        } //End of for x
    }    //End of for y
}
//Damages the enemy by dmgAmount
void Enemy::Damage(int dmgAmount, int i)
{
    life -= dmgAmount;
}
//TODO: To remove
void Enemy::Death()
{
}