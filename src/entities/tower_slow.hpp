#pragma once
#include "entity_tower.hpp"

class SlowTurret : public Turret
{
    public:
        SlowTurret()
        {
            range = NORMAL_TOWER_RANGE;
            towerClass = 1;
            maxCooldown = 5;
            shootingStrengh = 5;
        }
        int GetType() {return type;};
        float GetCooldown() {return maxCooldown;};
        //bool Spawn(ImVec2 pos, int type, Tilemap& tilemap);
};