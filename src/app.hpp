#pragma once
#include "tilemap.hpp"
#include "UI.hpp"
#include "entity.hpp"
#include "game.hpp"
class App
{
public:
    App();
    ~App();

    void Update();
    

    
    Tilemap* tilemap;
    Entity* entity;
    Game* game;
    Resources resources;
    ImDrawList* imdrawlist;
    UI* ui;
    ImGuiIO* io;

    
    float deltaTime;
    int scene = 0;
};

// GUIDE TO UNDERSTAND
/* 
- Resources | Contains every textures, sound, the game might use. Loaded on startup.


-Scene      | Handles scene processing. See constants.hpp to know more.
*/