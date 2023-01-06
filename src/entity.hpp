#pragma once
#include "tilemap.hpp"
#include "imgui_utils.hpp"

#define ENTITY_NUMBER       5           //Entity count on level one. Multiplied by LEVEL_ENTITY_MUL every level
#define LEVEL_ENTITY_MUL    1.2f
#define ENTITY_DISTANCE     0.25f/60.f  //Distance entity will teleport to while walking
class Entity
{
    public:
        Entity(Tilemap& tilemap);

        struct enemy {
            float   speed       = 0.1f;
            int direction       = 90;
            int life            = 10;
            int type            = 0;
            bool canStart       = false;

            ImVec2 pos          = {0,0};
        };

        enemy enemyArray[ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL /* * level*/)];
        void Update(ImDrawList& list, Resources& res, Tilemap& tilemap);
        void Draw(ImDrawList& list, Resources& res);
        void Movement(Tilemap& tilemap);
        
};