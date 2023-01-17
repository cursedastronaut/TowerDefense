#pragma once
#include "resources.hpp"
#include "game.hpp"
#include "tilemap.hpp"
#include "entity.hpp"
#include <cstdio>
#include <stdint.h>
#include <imgui.h>
#include <vector>

class UI
{
public:
    UI();
    ~UI();
    void Update(ImDrawList& list, Resources& res, Game* game, std::vector<Entity*>& EntityList /*Entity* entity,*/, Tilemap& tilemap);
    void Draw(ImDrawList& list, Resources& res, Game* game, std::vector<Entity*>& EntityList, Tilemap& tilemap);
    bool Button(Game* game, Texture tex, ImVec2 pos, float width, float height, ImVec4 col);
    bool dragDropButton(Texture tex, ImVec2 pos, ImVec2 widthHeight, ImVec4 col, Game* game, ImVec2 indexAndRange);
};