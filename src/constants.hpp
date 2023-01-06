#define windowWidth     1280
#define windowHeight    736


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
/*#define ENTITY_NUMBER       5       //Entity count on level one. Multiplied by LEVEL_ENTITY_MUL every level
#define LEVEL_ENTITY_MUL    1.2f*/

//Math things

struct float2 //NEVER TOUCH.
{
    float x;
    float y;  
};