#pragma once
#include "entity_tower.hpp"

class FastTurret : public Turret
{
    public:
        FastTurret()
        {
            range = NORMAL_TOWER_RANGE;
            towerClass = FAST_TOWERCLASS;
            maxCooldown = FAST_MAXCOOLDOWN;
            shootingStrength = FAST_ATTACK;
        }
        int GetType() {return type;};
        float GetCooldown() {return maxCooldown;};
};