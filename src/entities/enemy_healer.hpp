#pragma once
#include "entity_enemy.hpp"

class Healer : public Enemy
{
    public:

        Healer();
        Healer(Tilemap& tilemap) : Enemy(tilemap) 
        {
            speed = HEALER_MAXSPEED;
            maxSpeed = HEALER_MAXSPEED;
            enemyType = ENEMYTYPE_HEALER;
            attack = HEALER_ATTACK;
            cooldown = HEALER_COOLDOWN;
        };
        //Enemy functions
        float GetSpeed() {return speed;};
        float GetMaxSpeed() {return maxSpeed;};
        int GetClassType() {return enemyType;};
        void EditSpeed(float newSpeed) {speed = newSpeed;};
};