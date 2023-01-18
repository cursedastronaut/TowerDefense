#pragma once
#include "entity_enemy.hpp"

class Beefy : public Enemy
{
    public:

        Beefy();
        Beefy(Tilemap& tilemap) : Enemy(tilemap) 
        {
            speed = 0.05f;
            maxSpeed = 0.05f;
            enemyType = 1;
            attack = 3;
        };
        //Enemy functions
        float GetSpeed() {return speed;};
        float GetMaxSpeed() {return maxSpeed;};
        void EditSpeed(float newSpeed) {speed = newSpeed;};
};