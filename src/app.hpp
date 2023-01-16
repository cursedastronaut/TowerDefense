#pragma once
#include "resources.hpp"
#include <vector>

class Entity;
class Tilemap;
class Game;
class UI;

class App
{
public:
    App();
    ~App();
    //Main app processing
    void Update();
    
    Tilemap* tilemap;
    //Contains all the entities
    std::vector<Entity*> EntityList;
    Game* game;
    //Contains every textures, sound, the game might use. Loaded on startup.
    Resources resources;
    ImDrawList* imdrawlist;
    UI* ui;
    ImGuiIO* io;

    
    float deltaTime;
    //Handles scene processing. See constants.hpp to know more.
    int scene = 0;
    //Tells App::Update when to delete game values.
    bool restart = false;
};
