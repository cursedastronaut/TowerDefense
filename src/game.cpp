#include "game.hpp"
#include "imgui_utils.hpp"
#include "entities/entity_enemy.hpp"
#include "tilemap.hpp"
#include "constants.hpp"
#include <math.h>

void Game::LevelUpdate(std::vector<Entity*>& EntityList, Tilemap* tilemap)
{
    ImGui::Text("currentLevel: %d; wavesPassed: %d %f", currentLevel, levelProgression, levelProgCool);
    if (levelProgression < (INITIAL_ENEMY * currentLevel))
    {
        if (levelProgCool <= 0.f)
        {
            Enemy* newEntity = new Enemy(*tilemap);
            EntityList.push_back(newEntity);
            levelProgCool = 2.f;
            levelProgression ++;
        }
        
        levelProgCool -= ImGui::GetIO().DeltaTime;
    }/*
    else if ((INITIAL_ENEMY * currentLevel) + )
    {
    
    }*/
    
    
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
                        arrayTexlist[layer][z].text,
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

void Game::AddToTexlist(int z, int layer, ImTextureID id, ImVec2 posUL, ImVec2 posBR, ImVec2 uvUL, ImVec2 uvBR)
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

void Game::AddTextTexlist(int z, int layer, ImVec2 pos, ImU32 col, const char *text)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = pos;
    arrayTexlist[layer][z].text    = text;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 3;
}