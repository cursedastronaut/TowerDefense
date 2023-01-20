#pragma once
#include "entity_tower.hpp"

class SlowTurret : public Turret
{
    public:
        SlowTurret()
        {
            range = NORMAL_TOWER_RANGE;
            towerClass = SLOW_TOWERCLASS;
            maxCooldown = SLOW_MAXCOOLDOWN;
            shootingStrengh = SLOW_ATTACK;
        }
        int GetType() {return type;};
        float GetCooldown() {return maxCooldown;};
        //bool Spawn(ImVec2 pos, int type, Tilemap& tilemap);
};