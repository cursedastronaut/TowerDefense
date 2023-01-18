#pragma once
#include "tilemap.hpp"
#include "imgui_utils.hpp"
#include <vector>

#define ENTITY_NUMBER       5           //Entity count on level one. Multiplied by LEVEL_ENTITY_MUL every level
#define LEVEL_ENTITY_MUL    1.2f
#define ENTITY_DISTANCE     0.25f/60.f  //Distance entity will teleport to while walking

class Game;

class Entity
{
    public:
        Entity();
        virtual ~Entity();
        int type = -1;
        int life = -1;
        ImVec2 pos {-1,-1};
        bool canStart = false;
        
        virtual void Update(const std::vector<Entity*>& EntityList, Game* game) {};
        virtual void Draw(Game* game, Resources& res, int z);
        virtual bool Spawn(ImVec2 pos, int type, Tilemap& tilemap);
        virtual void Movement(Tilemap& tilemap);
        virtual void Damage(int dmgAmount, int i) {};
        virtual void Death() {};

        virtual int GetType() {return type;};
        virtual int GetLife() {return life;};
        virtual bool GetCanStart() {return false;};
        virtual ImVec2 GetPos() {return pos;};
        virtual float GetSpeed() {return 0;};
        virtual float GetMaxSpeed() {return 0;};
        virtual float GetAttack() {return 0;};
        virtual void EditSpeed(float newSpeed) {};
};