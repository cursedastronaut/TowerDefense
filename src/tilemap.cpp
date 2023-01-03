#include "tilemap.hpp"
#include "constants.hpp"
#include <stdio.h>
#include <cstdio>

Tilemap::Tilemap()
{
    FILE* f;
    uint32_t i;

    f = fopen("map1.bin", "r");
    if (!f)
    {
        printf("Can't open file");
        return;
    }

    i = 0;

    while (!feof(f))
    {
        m_grid[i++] = fgetc(f);
    }

    fclose(f);
}

Tilemap::~Tilemap()
{
}

void Tilemap::tilemapUpdate(ImDrawList& list, Resources& res)
{
    tilemapDraw(list, res);
}

void Tilemap::tilemapDraw(ImDrawList& list, Resources& res)
{
    //if (tileType)
    //printf("%d\n", tileType[2]);

    for (uint32_t y = 0; y < GRID_HEIGHT; y++)
    {
        for (uint32_t x = 0; x < GRID_HEIGHT; x++)
        {
            switch (m_grid[y * GRID_WIDTH + x])
            {
            case 1:
                list.AddImage(res.tileset.id, {x * 32, y * 32}, {x * 32 + 32, y * 32 + 32}, {0,0}, {TILE_HUV,TILE_VUV});
                break;

            case 2:
                list.AddImage(res.tileset.id, {x * 32, y * 32}, {x * 32 + 32, y * 32 + 32}, {TILE_HUV,0}, {TILE_HUV*2,TILE_VUV});
                break;
            
            default:
                break;
            }   
        }
    }
}