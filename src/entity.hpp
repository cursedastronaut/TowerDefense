#pragma once
#include "tilemap.hpp"
#include "game.hpp"
#include "imgui_utils.hpp"

#define ENTITY_NUMBER       5           //Entity count on level one. Multiplied by LEVEL_ENTITY_MUL every level
#define LEVEL_ENTITY_MUL    1.2f
#define ENTITY_DISTANCE     0.25f/60.f  //Distance entity will teleport to while walking
class Entity : public Game
{
    public:
        Entity(Tilemap& tilemap);
        
        void Update(Game* game, Resources& res, Tilemap& tilemap);
        void Draw(Game* game, Resources& res);
        void Movement(Tilemap& tilemap);
};