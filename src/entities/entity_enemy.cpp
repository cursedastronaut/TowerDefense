#include "../tilemap.hpp"
#include "../imgui_utils.hpp"
#include "../constants.hpp"
#include "entity_enemy.hpp"
#include <string>

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
                pos.x = x * TILE_SIZE + (TILE_SIZE / 2);
                pos.y = y * TILE_SIZE + (TILE_SIZE / 2);
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
        {pos.x - res.Fighter4.width / 8, pos.y - res.Fighter4.height / 8 - res.Fighter4.height / 8},  
        {pos.x + res.Fighter4.width / 8, pos.y + res.Fighter4.height / 8 - res.Fighter4.height / 8}, 
        // {pos.x + res.Fighter4.width / 2, pos.y + res.Fighter4.height / 2},                 
        uvUL,                           
        uvBR     
    );

}

void Enemy::Movement(Tilemap& tilemap)
{
    ImGuiIO* io = &ImGui::GetIO();
    float deltaTime = io->DeltaTime;
    ImGui::Text("Cooldown: [%f]", turnCooldown);
    // ImGui::Text("My lame ass deltatime be like: %f", deltaTime);
    ImGui::Text("Enemy type: %d", type);

    if (life <= 0)
        return;

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