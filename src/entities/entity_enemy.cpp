#include "../tilemap.hpp"
#include "../imgui_utils.hpp"
#include "../constants.hpp"
#include "entity_enemy.hpp"
#include <string>
#include <cmath>
#define PI 3.1415926535f

Enemy::Enemy()
{
}

Enemy::Enemy(Tilemap& tilemap)
    : direction(0)
{
    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            type = 1;
            if (tilemap.cGrid[y * GRID_WIDTH + x] == 0x06)
            {
                pos.x = x * TILE_SIZE;
                pos.y = (y-1) * TILE_SIZE;
            }
        }
    }
}

void Enemy::Draw(Game* game, Resources& res, int z)
{
    if (life <= 0)
    {
        return;
    }

    ImVec2 uvUL = {0,0};
    ImVec2 uvBR = {1,1};
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
    game->AddToTexlist(z, 10,
        res.Fighter4.id,                                                               
        {pos.x, pos.y},                                            
        {pos.x+res.Fighter4.width/4, pos.y+res.Fighter4.height/4},                 
        uvUL,                           
        uvBR     
    );
}

void Enemy::Movement(Tilemap& tilemap)
{
    ImGuiIO* io = &ImGui::GetIO();
    float deltaTime = io->DeltaTime;
    ImGui::Text("My lame ass deltatime be like: %f", deltaTime);
    
    ImGui::Text("Enemy type: %d", type);
    if (life <= 0)
        return;

    ImVec2 directionVec;

    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            //Handling directions
            
            switch (tilemap.cGrid[(int)(pos.y+TILE_SIZE) / TILE_SIZE * GRID_WIDTH + (int)pos.x / TILE_SIZE])
            {
                case 0x00:
                    break;
                case 0x02:
                    direction = 90;
                    directionVec = ImVec2(0, 1);
                    break;
                case 0x03:
                    direction = 0;
                    directionVec = ImVec2(1, 0);
                    break;
                case 0x04:
                    direction = 270;
                    directionVec = ImVec2(0, -1);
                    break;
                case 0x05:
                    direction = 180;
                    directionVec = ImVec2(-1, 0);
                    break;
                
                default:
                    break;
            }
            //Moves the player
            //pos.x += directionVec.x * Enemy::speed * ImGui::GetIO().DeltaTime;
            //pos.y += directionVec.y * Enemy::speed * ImGui::GetIO().DeltaTime;
            //pos.x += cosf(float(direction) / (2.f * PI)) * Enemy::speed * ImGui::GetIO().DeltaTime;
            //pos.y += -sinf((direction) / (2.f * PI)) * Enemy::speed * ImGui::GetIO().DeltaTime;
            switch (direction)
            {
                case 270:
                    pos.y += 2.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                case 00:
                    pos.x += 2.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                case 90:
                    pos.y -= 2.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                case 180:
                    pos.x -= 2.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                
                default:
                    break;
            }

            //float2 dirs[] = { { 0.f, 1.f }, { 1.f, 0.f }, { 0.f, 1.f }, { 0.f, 1.f } };
            //pos += speed * dirs[direction] * io.deltaTime;
        } //End of for x
    }    //End of for y
}
void Enemy::Damage(int dmgAmount, int i)
{
    life -= dmgAmount;
}

void Enemy::Death()
{
    printf("test");
}