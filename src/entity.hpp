#pragma once
#include "tilemap.hpp"
#include "game.hpp"
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

        class Turret {
            public:
                int     aimingAt = -1;
                int     type     = 0;
                int     level    = 0;
                float   cooldown = 0;
                ImVec2  pos      = {0,0};
                bool    active   = false;

                Turret();
        };
        Enemy enemyArray[ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL /* * level*/)];
        Turret turretArray[GRID_HEIGHT * GRID_WIDTH];
        void Update(Game* game, Resources& res, Tilemap& tilemap);
        void Draw(Game* game, Resources& res);
        void Movement(Tilemap& tilemap);

        
        //Enemy functions
        void drawEnemy(Game* game, Resources& res);
        void moveEnemy(Tilemap& tilemap);
        void damageEnemy(int dmgAmount, int i);
        void deathEnemy();

        //Turret functions
        void drawTower(Game* game, Resources& res);
        void spawnTower(ImVec2 pos, int type);
};