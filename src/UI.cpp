#include "UI.hpp"
#include "constants.hpp"

void UI::Draw(ImDrawList& list, Resources& res)
{
    list.AddRectFilled({250, windowHeight - 100}, {windowWidth - 250, windowHeight + 25}, IM_COL32(00, 00, 00, 88), 20.0f);
}

void UI::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
}