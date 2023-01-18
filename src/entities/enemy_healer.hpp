#pragma once
#include "entity_enemy.hpp"

class Healer : public Enemy
{
    public:

        Healer();
        Healer(Tilemap& tilemap) : Enemy(tilemap) 
        {
            speed = 0.15f;
            maxSpeed = 0.15f;
            enemyType = 2;
            attack = 1;
        };
        //Enemy functions
        float GetSpeed() {return speed;};
        float GetMaxSpeed() {return maxSpeed;};
        void EditSpeed(float newSpeed) {speed = newSpeed;};
};