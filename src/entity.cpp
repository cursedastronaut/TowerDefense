#include "entity.hpp"
#include "constants.hpp"
#include "game.hpp"

#include <string>

Entity::Entity()
{
    


    /*
    for (int i = 0; i < ENTITY_NUMBER * (LEVEL_ENTITY_MUL); i++)
    {
        enemyArray[i] = Enemy(tilemap);
    }
    for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        turretArray[i].type = 0;
    }*/
}

Entity::~Entity()
{
}

void Entity::Draw(Game* game, Resources& res, int z)
{
printf("AAAAAAA");

}

void Entity::Spawn(ImVec2 pos, int type, Tilemap& tilemap)
{}

void Entity::Movement(Tilemap& tilemap)
{
    //moveEnemy(tilemap);
}
/*void Damage(int dmgAmount, int i);
void Death();*/