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
        Entity();
        
         void Update(Game* game, Resources& res, Tilemap& tilemap);
        virtual void Draw(Game* game, Resources& res);
        virtual void Spawn(ImVec2 pos, int type, Tilemap& tilemap);
         void Movement(Tilemap& tilemap);
};