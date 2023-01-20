#pragma once
#include "entity_enemy.hpp"

class Beefy : public Enemy
{
    public:

        Beefy();
        Beefy(Tilemap& tilemap) : Enemy(tilemap) 
        {
            speed = BEEFY_MAXSPEED;
            maxSpeed = BEEFY_MAXSPEED;
            enemyType = ENEMYTYPE_BEEFY;
            attack = BEEFY_ATTACK;
        };
        //Enemy functions
        float GetSpeed() {return speed;};
        float GetMaxSpeed() {return maxSpeed;};
        void EditSpeed(float newSpeed) {speed = newSpeed;};
};