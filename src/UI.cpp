#include "UI.hpp"
#include "constants.hpp"

void UI::Draw(ImDrawList& list, Resources& res)
{
    ImVec2 towerSelectionUL = {windowWidth/2 - (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight - TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    ImVec2 towerSelectionBR = {windowWidth/2 + (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight + TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    //Background of Tower Selection Window
    list.AddRectFilled(
        towerSelectionUL,   //Upper-left point of rectangle
        towerSelectionBR,   //Bottom-right point of rectangle
        IM_COL32(00, 00, 00, 88),  //Color, black and transparent.
        20.0f //Rounding.
    );
    if (Button(list, res, {towerSelectionUL.x + 16, towerSelectionUL.y + 16}, TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT, {1,1,1,0.3f}) == true)
    {
        printf("pressed!");
    }
}

void UI::Update(ImDrawList& list, Resources& res)
{
    Draw(list, res);
}

bool UI::Button(ImDrawList& list, Resources& res, ImVec2 pos, float width, float height, ImVec4 col)
{
    bool isPressed = false;
    if (ImGui::IsMouseHoveringRect({ pos.x, pos.y}, { pos.x + width, pos.y + height}, false))
        col.w -= 0.1f; //Change alpha of button
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            isPressed = true;
        }
    ImU32 colorU32 = ImColor(col);
    //Background of Tower Selection Window
    list.AddRectFilled(
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + width, pos.y + height},   //Bottom-right point of rectangle
        colorU32,  //Color, black and transparent.
        20.0f //Rounding.
    );
    return isPressed;

}