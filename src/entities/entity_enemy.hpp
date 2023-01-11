/*#include "../entity.hpp"
class Enemy : public Entity {
    public:
        float   speed       = 0.1f;
        int     direction   = 90;
        int     life        = 10;
        int     type        = 0;
        bool    canStart    = false;

        Enemy();
        Enemy(Tilemap& tilemap);

        ImVec2 pos          = {0,0};
        //Enemy functions
        void drawEnemy(Game* game, Resources& res);
        void Move(Tilemap& tilemap);
        void damageEnemy(int dmgAmount, int i);
        void deathEnemy();
};*/