#pragma once
#include "imgui_utils.hpp"
#include "constants.hpp"
#include <vector>
#include <string>

class Entity;
class Tilemap;
class Resources;

class Game
{
    public:
        int money               = 2000;
        int currentLevel        = 1;
        int levelProgression    = 0;
        float levelProgCool     = 0;
        int castle_life         = 50;
        int dragDropIndex       = 0;
        bool gameover           = false;
        bool drawAiming         = false;

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
            std::string text;
        };
        
        Texlist arrayTexlist[32][MAX_TEXTURES];

        void LevelUpdate(std::vector<Entity*>& EntityList, Tilemap* tilemap, Resources& res, int* scene, bool* restart);

        void TexlistUpdate(ImDrawList& dl);
        void AddToTexlist(int z, int layer, ImTextureID id, ImVec2 posUL, ImVec2 posBR, ImVec2 uvUL, ImVec2 uvBR);
        void AddRectFilledTexlist(int z, int layer, ImVec2 posUL, ImVec2 posBR, ImU32 col = IM_COL32(0,0,0,0), float rounding = 20.0f);
        void AddRectTexlist(int z, int layer, ImVec2 posUL, ImVec2 posBR, ImU32 col = IM_COL32(0,0,0,0), float rounding = 20.0f, float thickness = 3.0f);
        void AddTextTexlist(int z, int layer, ImVec2 pos, ImU32 col = IM_COL32(0,0,0,0), std::string text = "");
};