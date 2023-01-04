#include "tilemap.hpp"
#include "constants.hpp"
#include <stdio.h>
#include <cstdio>

Tilemap::Tilemap()
{
    FILE* f;
    uint32_t i;

    f = fopen("map1.bin", "rb");
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
    }
    i = 0;

    //draws the tiles
    while (i < GRID_WIDTH * GRID_HEIGHT && !feof(f))
    {
        m_grid[i++] = fgetc(f);
    }

    fclose(f);
}

Tilemap::~Tilemap()
{
}

void Tilemap::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
}

void Tilemap::Draw(ImDrawList& list, Resources& res)
{
    //if (tileType)
    //printf("%d\n", tileType[2]);

    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_WIDTH; x++)
        {
            switch (m_grid[y * GRID_WIDTH + x])
            {
            case 1:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {0,0}, {TILE_HUV,TILE_VUV});
                break;

            case 2:
                list.AddImage(res.tileset.id, {x * (TILE_SIZE), y * (TILE_SIZE)}, {x * (TILE_SIZE) + (TILE_SIZE), y * (TILE_SIZE) + (TILE_SIZE)}, {TILE_HUV,0}, {TILE_HUV*2,TILE_VUV});
                break;
            
            default:
                break;
            }   
        }
    }
}