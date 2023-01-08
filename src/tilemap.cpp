#include "tilemap.hpp"
#include "constants.hpp"
#include <stdio.h>
#include <cstdio>

Tilemap::Tilemap()
{
    FILE*    f;
    FILE*    f2;
    uint32_t i;

    f =     fopen("assets/maps/map1.bin" , "rb");
    f2 =    fopen("assets/maps/path1.bin", "rb");
    if (!f)
    {
        printf("Can't open file");
        return;
    }

    i = 0;

    //cleans the memory before drawing the tiles
    while (i < GRID_WIDTH * GRID_HEIGHT)
    {
        mGrid[i++] = 0;
        cGrid[i]   = 0;
    }
    i = 0;

    //draws the tiles
    while (i < GRID_WIDTH * GRID_HEIGHT && !feof(f))
    {
        cGrid[i]   = fgetc(f2);
        mGrid[i++] = fgetc(f);
    }
    fclose(f);
    fclose(f2);
}

Tilemap::~Tilemap(){};

void Tilemap::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
    ImGui::Checkbox("Draw Path?", &drawPath);

}

void Tilemap::Draw(ImDrawList& list, Resources& res)
{

    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            float2 pos = {0,0};
            Texture tileSetToUse = res.tilesetWood;
            //ImU32 col = ImColor(0,0,0,0);
            switch (mGrid[y * GRID_WIDTH + x])
            {
                //Grass tile
                case 0:
                    pos.x = 0;  pos.y = 0;
                    break;

                //Cobblestone tile
                case 1:
                    pos.x = 1;  pos.y = 0;  break;

                //Castle tiles
                case 0xA0:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 0;  pos.y = 22; break;
                case 0xA1:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 0;  pos.y = 23; break;
                case 0xA2:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 0;  pos.y = 24; break;
                case 0xA3:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 7;  pos.y = 22; break;
                case 0xA4:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 1;  pos.y = 22; break;
                case 0xA5:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 6;  pos.y = 20; break;
                case 0xA6:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 0;  pos.y = 15; break;
                case 0xA7:
                    tileSetToUse = res.tilesetCastle;
                    pos.x = 0;  pos.y = 14; break;
                //                
                case 0xE0:
                    pos.x = 1;  pos.y = 26; break;
                case 0xE1:
                    pos.x = 0;  pos.y = 27; break;
                case 0xE2:
                    pos.x = 0;  pos.y = 26; break;
                case 0xEA:
                    pos.x = 6;  pos.y = 27; break;

                //Autotiles of cobblestones
                case 0xF0:
                    pos.x = 6;  pos.y = 25; break;
                    break;
                case 0xF1:
                    pos.x = 7;  pos.y = 25; break;
                    break;
                case 0xF3:
                    pos.x = 7;  pos.y = 26; break;
                case 0xF4:
                    pos.x = 6;  pos.y = 26; break;
                case 0xF7:
                    pos.x = 5;  pos.y = 28; break;
                case 0xF8:
                    pos.x = 5;  pos.y = 26; break;
                case 0xFA:
                    pos.x = 5;  pos.y = 27; break;
                case 0xFB:
                    pos.x = 4;  pos.y = 28; break;
                case 0xFC:
                    pos.x = 3;  pos.y = 28; break;
                case 0xFD:
                    pos.x = 3;  pos.y = 27; break;
                case 0xFE:
                    pos.x = 4;  pos.y = 26; break;
                case 0xFF:
                    pos.x = 3;  pos.y = 26; break;
                default:
                    break;
            }   
            list.AddImage(
                tileSetToUse.id,                                                                //Texture
                {x * (TILE_SIZE), y * (TILE_SIZE)},                                             //Position (upper-left) on Game Screen
                {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)},                 //Position (bottom-right) on Game Screen
                {(pos.x * TILE_SIZE)/tileSetToUse.width,                                        //UV (upper-right) position on tilesetWood
                (pos.y * TILE_SIZE)/tileSetToUse.height},                           
                {(pos.x * TILE_SIZE + TILE_SIZE) / tileSetToUse.width,                          //UV (bottom-left) position on tilesetWood
                 (pos.y * TILE_SIZE + TILE_SIZE) / tileSetToUse.height}     
            );
            
            pos = {0,0};
            if (drawPath)
            {
                switch (cGrid[y * GRID_WIDTH + x])
                {
                case 0x01: //Continue walking
                    pos = {0,0}; break;
                case 0x02: //Face north (upscreen)
                    pos = {1,0}; break;
                case 0x03: //Face east (left)
                    pos = {2,0}; break;
                case 0x04: //Face south (down)
                    pos = {3,0}; break;
                case 0x05: //Face west (right)
                    pos = {4,0}; break;
                case 0x06: //Spawnpoint
                    pos = {5,0}; break;
                default:
                    pos = {7,0};
                    break;
                }
                list.AddImage(
                    res.tilesetPath.id,
                    {x * (TILE_SIZE), y * (TILE_SIZE)},                                             //Position (upper-left) on Game Screen
                    {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)},                 //Position (bottom-right) on Game Screen
                    {(pos.x * TILE_SIZE)/res.tilesetPath.width,                                        //UV (upper-right) position on tilesetWood
                     (pos.y * TILE_SIZE)/res.tilesetPath.height},                           
                    {(pos.x * TILE_SIZE + TILE_SIZE) / res.tilesetPath.width,                          //UV (bottom-left) position on tilesetWood
                     (pos.y * TILE_SIZE + TILE_SIZE) / res.tilesetPath.height} 
                );
            }
        }
    }
}