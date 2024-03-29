#pragma once
#include "resources.hpp"
#include "game.hpp"
#include <cstdio>
#include <stdint.h>

//Grid size
#define GRID_WIDTH 40
#define GRID_HEIGHT 23

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();
    void Update(Game* game, Resources& res);
    void Draw(Game* game, Resources& res);

    
    uint8_t mGrid[GRID_WIDTH * GRID_HEIGHT];
    uint8_t cGrid[GRID_WIDTH * GRID_HEIGHT];
    bool drawPath = 0;
};