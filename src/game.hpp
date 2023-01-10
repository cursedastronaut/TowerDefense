#pragma once
#include "constants.hpp"
//#include "entities/entity_enemy.hpp"
//#include "entities/entity_tower.hpp"
//#include "tilemap.hpp"
class Game
{
    public:
        int money = 0;
        int dragDropIndex = 0;

        struct Texlist {
            bool active = false;
            ImTextureID id;
            ImVec2      posUL = {0,0};
            ImVec2      posBR = {0,0};
            ImVec2      uvUL  = {0,0};
            ImVec2      uvBR  = {0,0};
            ImU32       col   = IM_COL32(0,0,0,0);
            int         type  = 0;
            float       round = 0.0f;
            float       thick = 0.0f;
            const char *text;
        };

        Texlist arrayTexlist[MAX_TEXTURES];
        /*Enemy enemyArray[ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL)];
        Turret turretArray[GRID_HEIGHT * GRID_WIDTH];*/

        void TexlistUpdate(ImDrawList& dl);
        void AddToTexlist(int z, ImTextureID id, ImVec2 posUL, ImVec2 posBR, ImVec2 uvUL, ImVec2 uvBR);
        void AddRectFilledTexlist(int z, ImVec2 posUL, ImVec2 posBR, ImU32 col = IM_COL32(0,0,0,0), float rounding = 20.0f);
        void AddRectTexlist(int z, ImVec2 posUL, ImVec2 posBR, ImU32 col = IM_COL32(0,0,0,0), float rounding = 20.0f, float thickness = 3.0f);
        void AddTextTexlist(int z, ImVec2 pos, ImU32 col = IM_COL32(0,0,0,0), const char *text = "");
};