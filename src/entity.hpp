#pragma once
#include "tilemap.hpp"
#include "game.hpp"
#include "imgui_utils.hpp"
#include <vector>

#define ENTITY_NUMBER       5           //Entity count on level one. Multiplied by LEVEL_ENTITY_MUL every level
#define LEVEL_ENTITY_MUL    1.2f
#define ENTITY_DISTANCE     0.25f/60.f  //Distance entity will teleport to while walking
class Entity
{
    public:
        Entity();
        
        virtual void Update(const std::vector<Entity*>& EntityList) {};
        virtual void Draw(Game* game, Resources& res, int z);
        virtual void Spawn(ImVec2 pos, int type, Tilemap& tilemap);
        virtual void Movement(Tilemap& tilemap);
        virtual void Damage(int dmgAmount, int i) {};
        virtual void Death() {};
};