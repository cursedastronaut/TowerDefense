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

        class Enemy {
            public:
                float   speed       = 0.1f;
                int     direction   = 90;
                int     life        = 10;
                int     type        = 0;
                bool    canStart    = false;

                Enemy();
                Enemy(Tilemap& tilemap);

                ImVec2 pos          = {0,0};
        };

        class Tower {
            public:
                int     aimingAt = -1;
                int     type     = 0;
                float   cooldown = 0;
                ImVec2  pos      = {0,0};
                bool    active   = false;

                Tower();
        };
        Enemy enemyArray[ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL /* * level*/)];
        Tower towerArray[GRID_HEIGHT * GRID_WIDTH];
        void Update(ImDrawList& list, Resources& res, Tilemap& tilemap);
        void Draw(ImDrawList& list, Resources& res);
        void Movement(Tilemap& tilemap);
        
        //Enemy functions
        void drawEnemy(ImDrawList& list, Resources& res);
        void moveEnemy(Tilemap& tilemap);

        //Tower functions
        void drawTower(ImDrawList& list, Resources& res);
};