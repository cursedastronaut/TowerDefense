#pragma once
#include "entity_tower.hpp"

class SlowTurret : public Turret
{
    public:
        int     aimingAt = -1;
        int     type     = 0;
        int     level    = 0;
        float   range    = NORMAL_TOWER_RANGE;
        bool    active   = false;
        float   maxCooldown = 10.f;

        SlowTurret();
        int GetType() {return type;};
};