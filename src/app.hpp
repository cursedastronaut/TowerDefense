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
    
    Tilemap* tilemap;
    Entity* entity;
    Resources resources;
    ImDrawList* imdrawlist;
    UI* ui;
    ImGuiIO* io;

    float deltaTime;
    int scene = 0;
    
    //Game related content - Issue #15
    int money = 0;
    int dragDropIndex = 0;
};

// GUIDE TO UNDERSTAND
/* 
- Resources | Contains every textures, sound, the game might use. Loaded on startup.


-Scene      | Handles scene processing. See constants.hpp to know more.
*/