#pragma once
#include "resources.hpp"
#include <cstdio>
#include <stdint.h>
#include <imgui.h>

class UI
{
public:
    UI();
    ~UI();
    void Update(ImDrawList& list, Resources& res);
    void Draw(ImDrawList& list, Resources& res);
};