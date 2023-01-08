#pragma once
#include "resources.hpp"
#include "game.hpp"
#include "entity.hpp"
#include <cstdio>
#include <stdint.h>
#include <imgui.h>

class UI
{
public:
    UI();
    ~UI();
    void Update(ImDrawList& list, Resources& res, Game* game, Entity* entity);
    void Draw(ImDrawList& list, Resources& res, Game* game, Entity* entity);
    bool Button(ImDrawList& list, Texture tex, ImVec2 pos, float width, float height, ImVec4 col);
    bool dragDropButton(ImDrawList& list, Texture tex, ImVec2 pos, ImVec2 widthHeight, ImVec4 col, Game* game, int index);
};