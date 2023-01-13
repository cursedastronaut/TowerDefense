#pragma once
#include "../entity.hpp"
#include "../app.hpp"
class Enemy : public Entity {
    public:
        float   speed       = 0.1f;
        int     direction   = 90;
        int     life        = 10;
        int     type        = 1;
        bool    canStart    = true;

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
};