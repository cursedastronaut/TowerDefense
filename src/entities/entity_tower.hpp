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
        //Turret functions
        void Draw(Game* game, Resources& res, Tilemap& tilemap);
        void Spawn(ImVec2 pos, int type, Tilemap& tilemap);
        void Shoot();
};