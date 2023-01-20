#pragma once
#include "../entity.hpp"

class Turret : public Entity
{
    public:
        int     aimingAt = -1;
        int     towerClass = 0;
        int     type     = 0;
        int     level    = 0;
        float   range    = NORMAL_TOWER_RANGE;
        float   cooldown = 5.f;
        ImVec2  pos      = {0,0};
        bool    active   = false;
        float   maxCooldown = 1.5f;
        int     shootingStrengh = 3;

        Turret();
        //Turret functions
        void Update(const std::vector<Entity*>& EntityList, Game* game);
        void Draw(Game* game, Resources& res, int z) override ;
        bool Spawn(ImVec2 pos, Tilemap& tilemap, std::vector<Entity*>& EntityList);
        void Shoot(const std::vector<Entity*>& EntityList, Game* game);
        virtual float GetCooldown() {return maxCooldown;};
        int GetType() {return type;};
        int GetLevel() {return level;};
        int GetClassType() {return towerClass;};
        void EditLevel(int newLevel) {level = newLevel;};
        ImVec2 GetPos() {return pos;};
};