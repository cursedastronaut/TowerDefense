#include "../entity.hpp"

class Turret : public Entity
{
    public:
        int     aimingAt = -1;
        int     type     = 0;
        int     level    = 0;
        float   cooldown = 0;
        ImVec2  pos      = {0,0};
        bool    active   = false;

        Turret();

        //Enemy enemyArray[ENTITY_NUMBER * ((int)LEVEL_ENTITY_MUL /* * level*/)];
        //Turret turretArray[GRID_HEIGHT * GRID_WIDTH];
        void Update(Game* game, Resources& res, Tilemap& tilemap);
        void Draw(Game* game, Resources& res);
        void Movement(Tilemap& tilemap);
};