#pragma once
#include "../entity.hpp"

class Turret : public Entity
{
    public:
        int     aimingAt = -1;
        int     towerClass = NORMAL_TOWERCLASS;
        int     type     = ENTITYTYPE_TOWER;
        int     level    = 0;
        float   range    = NORMAL_TOWER_RANGE;
        float   cooldown = NORMAL_MAXCOOLDOWN;
        bool    active   = false;
        float   maxCooldown = NORMAL_MAXCOOLDOWN;
        int     shootingStrengh = NORMAL_ATTACK;

        Turret();
        //Turret functions
        void Update(std::vector<Entity*>& EntityList, Game* game);
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