#pragma once

//Gameplay settings
#define COST_TOWER          100
#define COST_TOWER_SLOW     200
#define NORMAL_TOWER_RANGE  10.f


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

