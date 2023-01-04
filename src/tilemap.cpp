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
        m_grid[i++] = 0;
        c_grid[i]   = 0;
    }
    i = 0;

    //draws the tiles
    while (i < GRID_WIDTH * GRID_HEIGHT && !feof(f))
    {
        m_grid[i++] = fgetc(f);
        c_grid[i]   = fgetc(f2);
    }

    fclose(f);
    fclose(f2);
}

Tilemap::~Tilemap(){};

void Tilemap::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
}

void Tilemap::Draw(ImDrawList& list, Resources& res)
{

    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            switch (m_grid[y * GRID_WIDTH + x])
            {
            //Grass tile
            case 0:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {0,0}, {TILE_HUV,TILE_VUV});
                break;
            //Cobblestone tile
            case 1:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {TILE_HUV,0}, {TILE_HUV*2,TILE_VUV});
                break;
            

            //Autotiles of cobblestones
            case 0xF0:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {192.f/256.f,799.f/928.f}, {(192.f+TILE_SIZE)/256.f, (799.f+TILE_SIZE)/928.f});
                break;
            case 0xF1:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {224.f/256.f,799.f/928.f}, {(224.f+TILE_SIZE)/256.f, (799.f+TILE_SIZE)/928.f});
                break;
            case 0xF3:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {224.f/256.f,831.f/928.f}, {(224.f+TILE_SIZE)/256.f, (831.f+TILE_SIZE)/928.f});
                break;
            case 0xF4:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {192.f/256.f,831.f/928.f}, {(192.f+TILE_SIZE)/256.f, (831.f+TILE_SIZE)/928.f});
                break;
            case 0xF7:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {160.f/256.f,895.f/928.f}, {(160.f+TILE_SIZE)/256.f, (895.f+TILE_SIZE)/928.f});
                break;
            case 0xF8:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {160.f/256.f,831.f/928.f}, {(160.f+TILE_SIZE)/256.f, (831.f+TILE_SIZE)/928.f});
                break;
            case 0xF9:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {160.f/256.f,895.f/928.f}, {(160.f+TILE_SIZE)/256.f, (895.f+TILE_SIZE)/928.f});
                break;
            case 0xFA:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {160.f/256.f,863.f/928.f}, {(160.f+TILE_SIZE)/256.f, (863.f+TILE_SIZE)/928.f});
                break; 
            case 0xFB:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {128.f/256.f,895.f/928.f}, {(128.f+TILE_SIZE)/256.f, (895.f+TILE_SIZE)/928.f});
                break; 
            case 0xFC:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {96.f/256.f,895.f/928.f}, {(96.f+TILE_SIZE)/256.f, (895.f+TILE_SIZE)/928.f});
                break;    
            case 0xFD:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {96.f/256.f,863.f/928.f}, {(96.f+TILE_SIZE)/256.f, (863.f+TILE_SIZE)/928.f});
                break;
            case 0xFE:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {(96.f+32.f)/256.f,831.f/928.f}, {(96.f+32.f+TILE_SIZE)/256.f, (831.f+TILE_SIZE)/928.f});
                break;
            case 0xFF:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {96.f/256.f,831.f/928.f}, {(96.f+TILE_SIZE)/256.f, (831.f+TILE_SIZE)/928.f});
                break;
            default:
                break;
            }   
            switch (c_grid[y * GRID_WIDTH + x])
            {
            case 1:
                list.AddRectFilled({(x-1) * (TILE_SIZE), y * (TILE_SIZE)}, {(x-1) * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, IM_COL32(255,0,0,128));
                break;
            default:
                break;
            }   
        }
    }
}