#pragma once
#include "entity_tower.hpp"

class FastTurret : public Turret
{
    public:
        FastTurret()
        {
            range = NORMAL_TOWER_RANGE;
            towerClass = 2;
            maxCooldown = 0.5f;
            shootingStrengh = 1;
        }
        int GetType() {return type;};
        float GetCooldown() {return maxCooldown;};
};