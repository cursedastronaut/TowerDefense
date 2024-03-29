#include "game.hpp"
#include "imgui_utils.hpp"
#include "entities/enemy_beefy.hpp"
#include "entities/enemy_healer.hpp"
#include "tilemap.hpp"
#include "constants.hpp"
#include <math.h>

void Game::LevelUpdate(std::vector<Entity*>& EntityList, Tilemap* tilemap, Resources& res, int* scene, bool* restart)
{
    if (enemyToSpawn > 0 && levelProgCool <= 0.f)
    {
        int randNum = rand()%(ENEMYTYPE_HEALER-ENEMYTYPE_WIMP + 1) + ENEMYTYPE_WIMP;
        spawnEnemy(EntityList, tilemap, randNum);
        levelProgCool = 2.f;
        enemyToSpawn -= 1;
    }
    if(enemyLeft <= 0 && enemyToSpawn <= 0)
    {
        currentLevel += 1;
        levelProgCool = 10.f;
        enemyToSpawn = INITIAL_ENEMY * currentLevel;
        enemyLeft = INITIAL_ENEMY * currentLevel;
    }
    levelProgCool -= ImGui::GetIO().DeltaTime;
    
    for (std::vector<Entity*>::iterator it = EntityList.begin(); it != EntityList.end(); )
    {
        Entity* e = *it;
        if (e->GetPos().x >= windowWidth)
        {
            castle_life -= e->GetAttack();
            it = EntityList.erase(it);
            delete e;
        }
        else
        {
            it++;
        }
    }
    if (castle_life <= 0 || ImGui::IsKeyReleased(ImGuiKey_Y))
        gameover = true;
    if (gameover)
    {
        if (EntityList.size())
        {
            for (size_t i = 0; i != EntityList.size(); i++)
            {
                delete EntityList[i];
            }
            EntityList.clear();
            
        }
        AddToTexlist(10,2, res.gameOver.id, {windowWidth/2.f - res.gameOver.width, windowHeight/2.f - res.gameOver.height},
        {windowWidth/2.f + res.gameOver.width, windowHeight/2.f + res.gameOver.height}, {0.f,0.f }, {1.f,1.f });
        if (ImGui::IsKeyReleased(ImGuiKey_MouseLeft))
        {
            *scene = SCENE_TITLE;
            *restart = true;
        }
    }
    
}

void Game::spawnEnemy(std::vector<Entity*>& EntityList, Tilemap* tilemap, int kind)
{
    if (kind == ENEMYTYPE_WIMP)
    {
        Enemy* newEntity = new Enemy(*tilemap);
        EntityList.push_back(newEntity); 
    }
    else if (kind == ENEMYTYPE_BEEFY)
    {
        Beefy* newEntity = new Beefy(*tilemap);
        EntityList.push_back(newEntity);
    }
    else if (kind == ENEMYTYPE_HEALER)
    {
        Healer* newEntity = new Healer(*tilemap);
        EntityList.push_back(newEntity);
    }
}


void Game::TexlistUpdate(ImDrawList& dl)
{
    for (int layer = 0; layer < 32; layer++)
    {
        for (int z = 0; z < MAX_TEXTURES; z++)
        {
            if (arrayTexlist[layer][z].active)
            {
                switch (arrayTexlist[layer][z].type)
                {
                case 0:
                    dl.AddImage(
                        arrayTexlist[layer][z].id,
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].posBR,
                        arrayTexlist[layer][z].uvUL,
                        arrayTexlist[layer][z].uvBR
                    );
                    break;
                case 1:
                    dl.AddRectFilled(
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].posBR,
                        arrayTexlist[layer][z].col,
                        arrayTexlist[layer][z].round
                    );
                    break;
                case 2:
                    dl.AddRect(
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].posBR,
                        arrayTexlist[layer][z].col,
                        arrayTexlist[layer][z].round,
                        0,
                        arrayTexlist[layer][z].thick
                    );
                    break;
                case 3:
                    dl.AddText(
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].col,
                        arrayTexlist[layer][z].text.c_str(),
                        NULL
                    );
                default:
                    break;
                }
                arrayTexlist[layer][z].active = false;
            }
        }
    }
}

void Game::AddToTexlist(int z, int layer, ImTextureID id, ImVec2 posUL, ImVec2 posBR, ImVec2 uvUL = {0,0}, ImVec2 uvBR = {1,1})
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].type    = 0;
    arrayTexlist[layer][z].id      = id;
    arrayTexlist[layer][z].posUL   = posUL;
    arrayTexlist[layer][z].posBR   = posBR;
    arrayTexlist[layer][z].uvUL    = uvUL;                          
    arrayTexlist[layer][z].uvBR    = uvBR;
    arrayTexlist[layer][z].col     = 0;
}

void Game::AddRectFilledTexlist(int z, int layer, ImVec2 posUL, ImVec2 posBR, ImU32 col, float rounding)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = posUL;
    arrayTexlist[layer][z].posBR   = posBR;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 1;
    arrayTexlist[layer][z].round   = rounding;
}

void Game::AddRectTexlist(int z, int layer, ImVec2 posUL, ImVec2 posBR, ImU32 col, float rounding, float thickness)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = posUL;
    arrayTexlist[layer][z].posBR   = posBR;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 2;
    arrayTexlist[layer][z].round   = rounding;
    arrayTexlist[layer][z].thick   = thickness;
}

void Game::AddTextTexlist(int z, int layer, ImVec2 pos, ImU32 col, std::string text)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = pos;
    arrayTexlist[layer][z].text    = text;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 3;
}