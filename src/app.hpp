#pragma once
#include "tilemap.hpp"
#include "resources.hpp"
class App
{
public:
    App();
    ~App();

    void Update();
    int money = 0;
    Tilemap* tilemap;
    Resources resources ;
    ImDrawList* imdrawlist;

};
