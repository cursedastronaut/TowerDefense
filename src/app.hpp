#pragma once
#include "tilemap.hpp"
#include "UI.hpp"
#include "entity.hpp"
#include "entities/entity_tower.hpp"
#include "entities/entity_enemy.hpp"
#include "game.hpp"
#include <vector>
class App
{
public:
    App();
    ~App();

    void Update();
    
    
    Tilemap* tilemap;
    //Entity* entity;
    //Tower* tower;
    std::vector<Entity*> EntityList;
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