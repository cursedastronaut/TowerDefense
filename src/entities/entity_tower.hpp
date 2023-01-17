#pragma once
#include "../entity.hpp"

class Turret : public Entity
{
    public:
        int     aimingAt = -1;
        int     type     = 0;
        int     level    = 0;
        float   range    = NORMAL_TOWER_RANGE;
        float   cooldown = 5.f;
        ImVec2  pos      = {0,0};
        bool    active   = false;
        int     maxCooldown = 5;

        Turret();
        //Turret functions
        void Update(const std::vector<Entity*>& EntityList, Game* game);
        void Draw(Game* game, Resources& res, int z) override ;
        bool Spawn(ImVec2 pos, int type, Tilemap& tilemap);
        void Shoot(const std::vector<Entity*>& EntityList, Game* game);
        virtual int GetCooldown() {return maxCooldown;};
        int GetType() {return type;};
        ImVec2 GetPos() {return pos;};
};