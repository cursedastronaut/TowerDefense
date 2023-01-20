#pragma once
#include "../entity.hpp"
#include "../app.hpp"

class Enemy : public Entity {
    public:
        float   speed       = 0.1f;
        float   maxSpeed    = 0.1f;
        int     direction   = 0;
        int     life        = 10;
        int     type        = 1;
        int     enemyType   = 0;
        int     attack      = 2;
        bool    canStart    = true;
        float   turnCooldown = (TILE_SIZE / 2) * speed;

        Enemy();
        Enemy(Tilemap& tilemap);

        ImVec2 pos          = {0,0};
        //Enemy functions
        void Draw(Game* game, Resources& res, int z);
        void Movement(Tilemap& tilemap);
        void Damage(int dmgAmount, int i);
        void Death(); 
        int GetType() {return type;};
        bool GetCanStart() {return canStart;};
        ImVec2 GetPos() {return pos;};
        int GetLife() {return life;};
        float GetSpeed() {return speed;};
        float GetMaxSpeed() {return maxSpeed;};
        float GetAttack() {return attack;};
        int GetClassType() {return enemyType;};
        void EditSpeed(float newSpeed) {speed = newSpeed;};
};