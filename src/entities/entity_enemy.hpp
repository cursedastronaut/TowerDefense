#pragma once
#include "../entity.hpp"
#include "../app.hpp"

class Enemy : public Entity {
    public:
        float   speed       = WIMP_MAXSPEED;
        float   maxSpeed    = WIMP_MAXSPEED;
        int     direction   = 0;
        int     type        = ENTITYTYPE_ENEMY;
        int     enemyType   = ENEMYTYPE_WIMP;
        float   cooldown    = 0;
        int     attack      = WIMP_ATTACK;
        bool    canStart    = true;
        float   turnCooldown = (TILE_SIZE / 2) * speed;

        Enemy();
        Enemy(Tilemap& tilemap);

        //Enemy functions
        void Draw(Game* game, Resources& res, int z);
        void Update(std::vector<Entity*>& EntityList, Game* game);
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