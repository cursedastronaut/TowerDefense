#pragma once

#define VERSION             "Version Beta 200123_25"

//Gameplay settings
#define COST_TOWER          100
#define COST_TOWER_SLOW     200
#define COST_TOWER_FAST     50
#define NORMAL_TOWER_RANGE  10.f
#define HEAL                2


//Tilemap settings
#define TILE_SIZE       32  //Size of the tile, default: 32x32

//UI settings
#define TOWER_WIN_WIDTH     0.8 //Percentage of screen-width that the Tower Selection UI will take
#define TOWER_WIN_HEIGHT    128 //Pixels that the Tower Selection UI will take
#define TOWER_ICON_HEIGHT   96 
#define TOWER_ICON_WIDTH    64

//Scenes
#define SCENE_TITLE         0
#define SCENE_GAME          1

//Entity settings
    //Number of entities spawning at the beginning of level 1. From level 2 and onwards,
    //it will be INITIAL_ENTITY + currentLevel. 
    #define INITIAL_ENEMY       3 
    //Number of entity to kill to finish a level (go to the final wave). Multiplied by currentLevel.
    #define MAX_ENEMY           15
    //Number of entity spawned during final wave. Multiplied by currentLevel.
    #define FINAL_WAVE_COUNT    5
    //Enemy settings
    #define ENTITYTYPE_ENEMY    1
        //Wimp (entity_enemy.hpp)
            #define ENEMYTYPE_WIMP      0 // Enum
            #define WIMP_MAXSPEED       0.1f
            #define WIMP_LIFE           10
            #define WIMP_ATTACK         2
            #define WIMP_DROP           100
        //Healer (enemy_healer.hpp)
            #define ENEMYTYPE_HEALER    2
            #define HEALER_MAXSPEED     0.15f
            #define HEALER_ATTACK       1
            #define HEALER_DROP         50
            #define HEALER_COOLDOWN     5.f
        //Beefy (ennemy_beefy.hpp)
            #define ENEMYTYPE_BEEFY     1
            #define BEEFY_MAXSPEED      0.05f
            #define BEEFY_ATTACK        3
            #define BEEFY_DROP          200
    
    //Tower settings
        #define ENTITYTYPE_TOWER        0
        //Normal tower
            #define NORMAL_TOWERCLASS   0
            #define NORMAL_MAXCOOLDOWN  1.5f
            #define NORMAL_ATTACK       3
        //Slow tower
            #define SLOW_TOWERCLASS     1
            #define SLOW_MAXCOOLDOWN    5
            #define SLOW_ATTACK         5
        //Fast tower
            #define FAST_TOWERCLASS     2
            #define FAST_MAXCOOLDOWN    0.5f
            #define FAST_ATTACK         1
//Graphics settings
#define windowWidth     1280
#define windowHeight    736
#define targetFPS       60.f //Max FPS
#define MAX_TEXTURES        2048
#define TILESET_Z           100
#define TILEPATH_Z          

//Math things

struct float2 //NEVER TOUCH.
{
    float x;
    float y;  
};

