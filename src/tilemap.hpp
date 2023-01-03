#pragma once
#include "resources.hpp"
#include <cstdio>
#include <stdint.h>

#define GRID_WIDTH 40
#define GRID_HEIGHT 23

class Tilemap
{
private:
    uint8_t m_grid[GRID_WIDTH * GRID_HEIGHT];

public:
    Tilemap();
    ~Tilemap();
    void tilemapUpdate(ImDrawList& list, Resources& res);
    void tilemapDraw(ImDrawList& list, Resources& res);
};