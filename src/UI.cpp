#include "UI.hpp"
#include "constants.hpp"

void UI::Draw(ImDrawList& list, Resources& res, Game* game)
{
    //draw a transparent white square on the tile the mouse is hovering
    list.AddRect(
        {int{ImGui::GetMousePos().x / 32} * 32, int{ImGui::GetMousePos().y / 32} * 32},   //Upper-left point of rectangle
        {int{ImGui::GetMousePos().x / 32} * 32 + 32, int{ImGui::GetMousePos().y / 32} * 32 + 32},   //Bottom-right point of rectangle
        IM_COL32_WHITE,  //Color, black and transparent.
        3.0f, //Rounding.
        0,
        3.0f //outline thickness.
    );

    ImVec2 towerSelectionUL = {windowWidth/2 - (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight - TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    ImVec2 towerSelectionBR = {windowWidth/2 + (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight + TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    //Background of Tower Selection Window
    list.AddRectFilled(
        towerSelectionUL,   //Upper-left point of rectangle
        towerSelectionBR,   //Bottom-right point of rectangle
        IM_COL32(00, 00, 00, 88),  //Color, black and transparent.
        20.0f //Rounding.
    );
    list.AddText({towerSelectionUL.x + 16, towerSelectionUL.y + 1}, 
        0xFFFFFFFF, "Choose your tower", NULL);
    if (dragDropButton(list, res.tilesetCastle, {towerSelectionUL.x + 16, towerSelectionUL.y + 16}, {TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT}, {1,1,1,0.3f}, game, 1) == true)
    {
        
    }
}

void UI::Update(ImDrawList& list, Resources& res, Game* game)
{
    Draw(list, res, game);
}

bool UI::Button(ImDrawList& list, Texture tex, ImVec2 pos, float width, float height, ImVec4 col)
{
    bool isPressed = false;
    if (ImGui::IsMouseHoveringRect({ pos.x, pos.y}, { pos.x + width, pos.y + height}, false))
    {
        col.w += 0.1f; //Change alpha of button
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            isPressed = true;
            col.w += 0.1f;
        }
    }
        
    ImU32 colorU32 = ImColor(col);
    //Background of Tower Selection Window
    list.AddRectFilled(
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + width, pos.y + height},   //Bottom-right point of rectangle
        colorU32,  //Color, black and transparent.
        20.0f //Rounding.
    );
    list.AddImage(
                tex.id,
                { pos.x, pos.y},
                { pos.x + width, pos.y + height},
                {0,0},                           
                {1,1}     
            );
    return isPressed;

}

bool UI::dragDropButton(ImDrawList& list, Texture tex, ImVec2 pos, ImVec2 widthHeight, ImVec4 col, Game* game,int index)
{
    bool isPressed = false;
    if (ImGui::IsMouseHoveringRect({ pos.x, pos.y}, { pos.x + widthHeight.x, pos.y + widthHeight.y}, false))
    {
        col.w += 0.1f; //Change alpha of button
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            isPressed = true;
            game->dragDropIndex = index; //Solve issue #15 first.
            ImGui::Text("dragDropIndex: %d", game->dragDropIndex);
            col.w += 0.1f;
        }
    }
        
    ImU32 colorU32 = ImColor(col);
    //Background of Tower Selection Window
    list.AddRectFilled(
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + widthHeight.x, pos.y + widthHeight.y},   //Bottom-right point of rectangle
        colorU32,  //Color, black and transparent.
        20.0f //Rounding.
    );
    list.AddImage(
                tex.id,
                { pos.x, pos.y},
                { pos.x + widthHeight.x, pos.y + widthHeight.y},
                {0,0},                           
                {1,1}     
            );
    return isPressed;

}