#pragma once
#include "entity_tower.hpp"

class SlowTurret : public Turret
{
    public:
        SlowTurret()
        {
            range = NORMAL_TOWER_RANGE;
            maxCooldown = 10;
        }
        int GetType() {return type;};
        int GetCooldown() {return maxCooldown;};
        //bool Spawn(ImVec2 pos, int type, Tilemap& tilemap);
};