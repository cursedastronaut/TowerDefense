#pragma once
#include "resources.hpp"
#include <cstdio>
#include <stdint.h>

#define GRID_WIDTH 0x1E
#define GRID_HEIGHT (0x1FE / GRID_WIDTH)

class Tilemap
{
private:
    uint8_t m_grid[GRID_WIDTH * GRID_HEIGHT];

public:
    Tilemap();
    ~Tilemap();
    void Update(ImDrawList& list, Resources& res);
    void Draw(ImDrawList& list, Resources& res);
};