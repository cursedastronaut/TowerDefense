#include "../tilemap.hpp"
#include "../imgui_utils.hpp"d
#include "../constants.hpp"
#include "entity_enemy.hpp"
#include <string>

Enemy::Enemy()
{
}

Enemy::Enemy(Tilemap& tilemap)
    : direction(90)
{
    /*
    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            type = 1;
            if (tilemap.cGrid[y * GRID_WIDTH + x] == 0x06)
            {
                pos.x = x * TILE_SIZE;
                pos.y = (y-1) * TILE_SIZE;
                //direction = 90;
            }
        }
    }*/
}

void Enemy::drawEnemy(Game* game, Resources& res)
{/*
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
    {
        if (!enemyArray[i].canStart || enemyArray[i].life <= 0)
        {
            return;
        }

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
        game->AddToTexlist( 3000+i,
            res.Fighter4.id,                                                               
            {enemyArray[i].pos.x, enemyArray[i].pos.y},                                            
            {enemyArray[i].pos.x+res.Fighter4.width/4, enemyArray[i].pos.y+res.Fighter4.height/4},                 
            uvUL,                           
            uvBR     
        );
    }*/
}

void Enemy::moveEnemy(Tilemap& tilemap)
{/*
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
    {
        if (ImGui::Button(std::string("Enemy Start").append(std::to_string(i)).c_str())) {
            enemyArray[i].canStart = true;
        }
        if (!enemyArray[i].canStart || enemyArray[i].life <= 0)
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
                        enemyArray[i].pos.y += 0.25f/60.f;
                        break;
                    case 90:
                        enemyArray[i].pos.x += 0.25f/60.f;
                        break;
                    case 0:
                        enemyArray[i].pos.y -= 0.25f/60.f;
                        break;
                    case 270:
                        enemyArray[i].pos.x -= 0.25f/60.f;
                        break;
                    
                    default:
                        break;
                }

                //float2 dirs[] = { { 0.f, 1.f }, { 1.f, 0.f }, { 0.f, 1.f }, { 0.f, 1.f } };
                //enemyArray[i].pos += speed * dirs[enemyArray[i].direction] * io.deltaTime;
            } //End of for x
        }    //End of for y
    }*/
}
void Enemy::damageEnemy(int dmgAmount, int i)
{/*
    enemyArray[i].life -= dmgAmount;*/
}
/*
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
        if (collision == true)
            damageEnemy(4, i);
*/
void Enemy::deathEnemy()
{/*
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
    {
        enemyArray[i].life = 0;
    }*/
}