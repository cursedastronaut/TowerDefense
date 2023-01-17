#pragma once
#include "entity_tower.hpp"

class FastTurret : public Turret
{
    public:
        FastTurret()
        {
            range = NORMAL_TOWER_RANGE;
            maxCooldown = 2;
            shootingStrengh = 1;
        }
        int GetType() {return type;};
        int GetCooldown() {return maxCooldown;};
};