#pragma once
#include "tilemap.hpp"
#include "UI.hpp"
#include "entity.hpp"
class App
{
public:
    App();
    ~App();

    void Update();
    int money = 0;
    Tilemap* tilemap;
    Entity* entity;
    Resources resources;
    ImDrawList* imdrawlist;
    UI* ui;

    int scene = 0;
};

// GUIDE TO UNDERSTAND
/* 
- Resources | Contains every textures, sound, the game might use. Loaded on startup.


-Scene      | Handles scene processing. See constants.hpp to know more.
*/