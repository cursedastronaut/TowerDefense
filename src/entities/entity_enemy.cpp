#include "../tilemap.hpp"
#include "../imgui_utils.hpp"
#include "../constants.hpp"
#include "entity_enemy.hpp"
#include <string>

Enemy::Enemy()
{
}

Enemy::Enemy(Tilemap& tilemap)
    : direction(90)
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
    if (!canStart || life <= 0)
    {
        return;
    }

    ImVec2 uvUL = {0,0};
    ImVec2 uvBR = {1,1};
    switch (direction)
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
    
    ImGui::Text("Enemy type: %d Enemy CanStart : %d", type, canStart);
    if (ImGui::Button(std::string("Enemy Start").append(std::to_string(0)).c_str())) {
        canStart = true;
    }
    if (!canStart || life <= 0)
        return;

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
                    direction = 0;
                    break;
                case 0x03:
                    direction = 90;
                    break;
                case 0x04:
                    direction = 180;
                    break;
                case 0x05:
                    direction = 270;
                    break;
                
                default:
                    break;
            }
            //Moves the player
            switch (direction)
            {
                case 180:
                    pos.y += 1.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                case 90:
                    pos.x += 1.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                case 0:
                    pos.y -= 1.f/20.f * ImGui::GetIO().DeltaTime;
                    break;
                case 270:
                    pos.x -= 1.f/20.f * ImGui::GetIO().DeltaTime;
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

    /*for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
        if (collision == true)
            damageEnemy(4, i);*/
}

void Enemy::Death()
{
    
}