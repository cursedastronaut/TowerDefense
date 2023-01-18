#pragma once
#include "entity_enemy.hpp"

class Beefy : public Enemy
{
    public:
        float   speed       = 0.05f;
        float   maxSpeed    = 0.05f;

        Wimp();
        Wimp(Tilemap& tilemap);
        //Enemy functions
        float GetSpeed() {return speed;};
        float GetMaxSpeed() {return maxSpeed;};
        void EditSpeed(float newSpeed) {speed = newSpeed;};
};