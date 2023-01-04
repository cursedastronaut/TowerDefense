#include "UI.hpp"
#include "constants.hpp"

void UI::Draw(ImDrawList& list, Resources& res)
{
    list.AddRectFilled({250, windowHeight - 100}, {windowWidth - 250, windowHeight + 25}, IM_COL32(00, 00, 00, 88), 20.0f);
    // list.AddRectFilled({windowWidth / 2 - 40, windowHeight - 90}, {windowWidth / 2 + 40, windowHeight - 10}, IM_COL32(00, 00, 255, 88));
    ImGui::Button("tower", {50, 50});
}

void UI::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
}