#include "UI.hpp"
#include "constants.hpp"
#include "entities/tower_slow.hpp"
#include "entities/tower_fast.hpp"
#include <string>

void UI::Draw(ImDrawList& list, Resources& res, Game* game, std::vector<Entity*>& EntityList, Tilemap& tilemap)
{
    //draw a transparent white square on the tile the mouse is hovering
    game->AddRectTexlist( 100, 5,
        { (float)int(ImGui::GetMousePos().x / 32) * 32, (float)int(ImGui::GetMousePos().y / 32) * 32},   //Upper-left point of rectangle
        { (float)int(ImGui::GetMousePos().x / 32) * 32 + 32, (float)int(ImGui::GetMousePos().y / 32) * 32 + 32},   //Bottom-right point of rectangle
        IM_COL32_WHITE,  //Color, black and transparent.
        3.0f, //Rounding.
        3.0f //outline thickness.
    );

    ImVec2 towerSelectionUL = {windowWidth/2 - (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight - TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    ImVec2 towerSelectionBR = {windowWidth/2 + (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight + TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    //Background of Turret Selection Window
    game->AddRectFilledTexlist( 9, 5,
        towerSelectionUL,   //Upper-left point of rectangle
        towerSelectionBR,   //Bottom-right point of rectangle
        IM_COL32(00, 00, 00, 88),  //Color, black and transparent.
        20.0f //Rounding.
    );
    game->AddTextTexlist(64, 5,
    {towerSelectionUL.x + 16, towerSelectionUL.y + 1}, 
        0xFFFFFFFF, "Choose your tower");

    //displays the price of the different towers
    std::string towerCost[] = {"", "", ""};
    towerCost[0] = std::to_string(COST_TOWER);
    towerCost[1] = std::to_string(COST_TOWER_SLOW);
    towerCost[2] = std::to_string(COST_TOWER_FAST);
    for(int i = 0; i <= 2; i++)
    {
        game->AddTextTexlist(10 + i, 5,
            {towerSelectionUL.x + 16 + (80 * i), towerSelectionUL.y + 112}, //position of text
            IM_COL32_WHITE, //color of text
            towerCost[i] //the text itself
        );
    }

    if (dragDropButton(res.Turret, {towerSelectionUL.x + 16, towerSelectionUL.y + 16}, {TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT}, {1,1,1,0.3f}, game, {1, NORMAL_TOWER_RANGE, 30, 5}) == true)
    {
        if (game->money >= COST_TOWER)
        {
            Turret* newEntity = new Turret();
            if (newEntity->Spawn({ImGui::GetMousePos().x,ImGui::GetMousePos().y}, tilemap, EntityList))
                game->money -= COST_TOWER;
            EntityList.push_back(newEntity);
        }
    } 
    if (dragDropButton(res.Turret, {towerSelectionUL.x + 96, towerSelectionUL.y + 16}, {TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT}, {1,1,1,0.3f}, game, {2, NORMAL_TOWER_RANGE, 40, 5}, {0,0.25f,0.25f,0.5f}) == true)
    {
        if (game->money >= COST_TOWER_SLOW)
        {
            SlowTurret* newEntity = new SlowTurret();
            if (newEntity->Spawn({ImGui::GetMousePos().x,ImGui::GetMousePos().y}, tilemap, EntityList))
                game->money -= COST_TOWER_SLOW;
            EntityList.push_back(newEntity);
        }
    }
    if (dragDropButton(res.Turret, {towerSelectionUL.x + 96 + 80, towerSelectionUL.y + 16}, {TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT}, {1,1,1,0.3f}, game, {3, NORMAL_TOWER_RANGE, 50, 5}, {0.5f,0,0.75f,0.25f}) == true)
    {
        if (game->money >= COST_TOWER_FAST)
        {
            FastTurret* newEntity = new FastTurret();
            if (newEntity->Spawn({ImGui::GetMousePos().x,ImGui::GetMousePos().y}, tilemap, EntityList))
                game->money -= COST_TOWER_FAST;
            EntityList.push_back(newEntity);
        }
    }

    // Attempt at simplifying the repetitive code above

        // for(int i = 0; i <= 2; i++)
        // {
        //     if (dragDropButton(res.Turret, {towerSelectionUL.x + 16 + (80 * i), towerSelectionUL.y + 16}, {TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT}, {1,1,1,0.3f}, game, {i + 1, NORMAL_TOWER_RANGE, 30 + (10 * i), 5}, /*{0.5f,0,0.75f,0.25f}*/) == true)
        //     {
        //         if (game->money >= COST_TOWER)
        //         {
        //             FastTurret* newEntity = new FastTurret();
        //             if (newEntity->Spawn({ImGui::GetMousePos().x,ImGui::GetMousePos().y}, 0, tilemap))
        //                 game->money -= COST_TOWER_FAST;
        //             EntityList.push_back(newEntity);
        //         }
        //     }        
        // }

    game->AddRectFilledTexlist(0,5, {8, 8}, {128, 48}, 0x80000000, 5.f);
    std::string nara = "Money : ";
    nara += std::to_string(game->money);
    game->AddTextTexlist(1,5, {16,16}, 0xFFFFFFFF, nara);
}

void UI::Update(ImDrawList& list, Resources& res, Game* game, std::vector<Entity*>& EntityList /*Entity* entity,*/, Tilemap& tilemap)
{
    if (game->gameover)
        return;
    Draw(list, res, game, EntityList/*entity,*/, tilemap);
    ImGui::Text("dragDropIndex: %d", game->dragDropIndex);
}

bool UI::Button(Game* game, Texture tex, ImVec2 pos, float width, float height, ImVec4 col)
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
    //Background of Turret Selection Window
    game->AddRectFilledTexlist(29, 5,
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + width, pos.y + height},   //Bottom-right point of rectangle
        colorU32,  //Color, black and transparent.
        20.0f //Rounding.
    );
    game->AddToTexlist( 30 , 5,
                tex.id,
                { pos.x, pos.y},
                { pos.x + width, pos.y + height},
                {0,0},
                {1,1}     
            );
    return isPressed;

}

bool UI::dragDropButton(Texture tex, ImVec2 pos, ImVec2 widthHeight, ImVec4 col, Game* game, ImVec4 indexAndRange, ImVec4 uv)
{
    bool isDropped = false;
    if (ImGui::IsMouseHoveringRect({ pos.x, pos.y}, { pos.x + widthHeight.x, pos.y + widthHeight.y}, false))
    {
        col.w += 0.1f; //Change alpha of button
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            game->dragDropIndex = indexAndRange.x;
            col.w += 0.1f;
        }
    }
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && game->dragDropIndex == indexAndRange.x)
    {
        col.w += 0.1f;
        indexAndRange.y *= TILE_SIZE;
        game->AddRectFilledTexlist(indexAndRange.z+2, indexAndRange.w, 
                { (int)(ImGui::GetMousePos().x/32)*32 - indexAndRange.y/2+16, (int)(ImGui::GetMousePos().y/32)*32 - indexAndRange.y/2+16},
                { (int)(ImGui::GetMousePos().x/32)*32 + indexAndRange.y/2+16, (int)(ImGui::GetMousePos().y/32)*32 + indexAndRange.y/2+16}
                , 0x80FFFFFF, 9999999999.f);
        game->AddToTexlist(
                indexAndRange.z+3,indexAndRange.w,
                tex.id,
                { (int)(ImGui::GetMousePos().x/32)*32.f, (int)(ImGui::GetMousePos().y/32)*32.f - tex.height/8.f },
                { (int)(ImGui::GetMousePos().x/32)*32.f + tex.width/4.f, (int)(ImGui::GetMousePos().y/32)*32 + tex.height/8.f },
                {uv.x,uv.y},
                {uv.z,uv.w}
            );
    }    
    else
    {
        if(game->dragDropIndex == indexAndRange.x)
        {
            game->dragDropIndex = 0;
            isDropped = true;  
        }
    }
    ImU32 colorU32 = ImColor(col);
    //Background of Turret Selection Window
    game->AddRectFilledTexlist(indexAndRange.z, indexAndRange.w,
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + widthHeight.x, pos.y + widthHeight.y},   //Bottom-right point of rectangle
        colorU32,  //Color, black and transparent.
        10.0f //Rounding.
    );
    game->AddToTexlist( indexAndRange.z+1 , indexAndRange.w,
                tex.id,
                { pos.x, pos.y},
                { pos.x + widthHeight.x, pos.y + widthHeight.y},
                {uv.x,uv.y},
                {uv.z,uv.w}
            );
    return isDropped;

}