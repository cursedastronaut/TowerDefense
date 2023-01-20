#include "UI.hpp"
#include "constants.hpp"
#include "entities/tower_slow.hpp"
#include "entities/tower_fast.hpp"
#include <string>
#include "calc.hpp"
void UI::Draw(ImDrawList& list, Resources& res, Game* game, std::vector<Entity*>& EntityList, Tilemap& tilemap)
{
    //Draw a white crosshair on the tile that the player is aiming at
    game->AddRectTexlist( 100, 5,
        { (float)int(ImGui::GetMousePos().x / 32) * 32, (float)int(ImGui::GetMousePos().y / 32) * 32},   //Upper-left point of rectangle
        { (float)int(ImGui::GetMousePos().x / 32) * 32 + 32, (float)int(ImGui::GetMousePos().y / 32) * 32 + 32},   //Bottom-right point of rectangle
        IM_COL32_WHITE,  //Color, white
        3.0f, //Rounding
        3.0f //Outline thickness
    );

    ImVec2 towerSelectionUL = {windowWidth/2 - (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight - TOWER_WIN_HEIGHT};   //Upper-left point of rectangle
    ImVec2 towerSelectionBR = {windowWidth/2 + (TOWER_WIN_WIDTH * windowWidth)/2, windowHeight + TOWER_WIN_HEIGHT};   //Lower-right point of rectangle
    
    //Background of Turret Selection Window
    game->AddRectFilledTexlist( 9, 5,
        towerSelectionUL,   //Upper-left point of rectangle
        towerSelectionBR,   //Bottom-right point of rectangle
        IM_COL32(00, 00, 00, 88),  //Color, white
        20.0f //Rounding
    );
    //UI text telling you to choose your tower
    game->AddTextTexlist(64, 5,
    {towerSelectionUL.x + 16, towerSelectionUL.y + 1}, 
        0xFFFFFFFF, "Choose your tower");

    //Displays the price of the different towers
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

    //Generates the drag & drop tower buttons at the bottom of the screen
    for(int i = 0; i <= 2; i++)
    {
        ImVec4 UVtoUse;

        //Sets the correct UV coordinates in "UVtoUse"
        switch(i)
        {
            case NORMAL_TOWERCLASS: UVtoUse = {0.f, 0.f, 0.25f, 0.25f}; break;
            case SLOW_TOWERCLASS: UVtoUse = {0.f, 0.25f, 0.25f, 0.5f}; break;
            case FAST_TOWERCLASS: UVtoUse = {0.5f, 0.f, 0.75f, 0.25f}; break;
        }

        //Draws and process the tower drag and drop button
        if (dragDropButton(res.Turret, {towerSelectionUL.x + 16 + (80 * i), towerSelectionUL.y + 16}, {TOWER_ICON_WIDTH, TOWER_ICON_HEIGHT}, {1,1,1,0.3f}, game, {(float)i + 1, NORMAL_TOWER_RANGE, (float)(30 + (10 * i)), 5}, UVtoUse) == true)
        {
            int costTower;
            //Sets the correct price in "costTower". this value will be used to display the price below each buttons and also
            //to subtract said price when a turret is placed
            switch(i)
            {
                case NORMAL_TOWERCLASS: costTower = COST_TOWER; break;
                case SLOW_TOWERCLASS: costTower = COST_TOWER_SLOW; break;
                case FAST_TOWERCLASS: costTower = COST_TOWER_FAST; break;
            }            
            //Checks if player has enough money
            if (game->money >= costTower)
            {
                //Actual creation of the entity
                Turret* newEntity;
                //Sets the correct tower type (and its default values) in newEntity.
                switch(i)
                {
                    case NORMAL_TOWERCLASS: newEntity = new Turret(); break;
                    case SLOW_TOWERCLASS: newEntity = new SlowTurret(); break;
                    case FAST_TOWERCLASS: newEntity = new FastTurret(); break;
                    default: newEntity = new Turret(); break;
                }
                //Checks the placement of the turret, and substract the cost if it succeeded
                if (newEntity->Spawn({ImGui::GetMousePos().x,ImGui::GetMousePos().y}, tilemap, EntityList))
                {
                    game->money -= costTower;
                }
                //Pushback the entity to the EntityList. Turret has been created.
                EntityList.push_back(newEntity);                    
            }
        }        
    }
    //Displays money
    game->AddRectFilledTexlist(0,5, {8, 8}, {128, 48}, 0x80000000, 5.f);
    std::string nara = "Money : ";
    nara += std::to_string(game->money);
    game->AddTextTexlist(1,5, {16,16}, 0xFFFFFFFF, nara);
}

void UI::Update(ImDrawList& list, Resources& res, Game* game, std::vector<Entity*>& EntityList, Tilemap& tilemap)
{
    if (game->gameover)
        return;
    Draw(list, res, game, EntityList , tilemap);
}

//Draws and process a button.
bool UI::Button(Game* game, Texture tex, ImVec2 pos, float width, float height, ImVec4 col)
{
    bool isPressed = false;
    //If mouse is hovering the button
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
    //Draws background of Turret Selection Button
    game->AddRectFilledTexlist(29, 5,
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + width, pos.y + height},   //Bottom-right point of rectangle
        colorU32,                           //Color, black and transparent.
        20.0f                               //Rounding.
    );
    //Draws the button icon.
    game->AddToTexlist( 30 , 5, //Since it is only used once, this is ok.
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
    //If Mouse is hovering the button, we slightly increase the button alpha.
    if (ImGui::IsMouseHoveringRect({ pos.x, pos.y}, { pos.x + widthHeight.x, pos.y + widthHeight.y}, false))
    {
        col.w += 0.1f; //Change alpha of button
        //If Mouse is hovering and clicking, the alpha is changed again, and it remembers what button is dragged.
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            game->dragDropIndex = indexAndRange.x;
            col.w += 0.1f;
        }
    }
    //If the button is being dragged, change the alpha and do the following
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && game->dragDropIndex == indexAndRange.x)
    {
        col.w += 0.1f;
        indexAndRange.y *= TILE_SIZE;
        //Draws the tower range around the tile the mouse is hovering
        game->AddRectFilledTexlist(indexAndRange.z+2, indexAndRange.w, 
                { Calc::MousePositionWorld().x - (indexAndRange.y/2)+(TILE_SIZE/2), Calc::MousePositionWorld().y - (indexAndRange.y/2)+(TILE_SIZE/2)},
                { Calc::MousePositionWorld().x + (indexAndRange.y/2)+(TILE_SIZE/2), Calc::MousePositionWorld().y + (indexAndRange.y/2)+(TILE_SIZE/2)}
                , 0x80FFFFFF, 9999999999.f);
        //Draw the tower above the tile the mouse is hovering
        game->AddToTexlist(
                indexAndRange.z+3,indexAndRange.w,
                tex.id,
                { Calc::MousePositionWorld().x                  , Calc::MousePositionWorld().y - tex.height/8.f},
                { Calc::MousePositionWorld().x + tex.width/4.f  , Calc::MousePositionWorld().y + tex.height/8.f},
                {uv.x,uv.y},
                {uv.z,uv.w}
            );
    }    
    else
    {
        //Returns true if dropped after drag.
        if(game->dragDropIndex == indexAndRange.x)
        {
            game->dragDropIndex = 0;
            isDropped = true;  
        }
    }
    ImU32 colorU32 = ImColor(col);
    //Draws background of Turret Selection Button
    game->AddRectFilledTexlist(indexAndRange.z, indexAndRange.w,
        { pos.x, pos.y},                    //Upper-left point of rectangle
        { pos.x + widthHeight.x, pos.y + widthHeight.y},   //Bottom-right point of rectangle
        colorU32,  //Color, black and transparent.
        10.0f //Rounding.
    );
    //Draws the turret icon
    game->AddToTexlist( indexAndRange.z+1 , indexAndRange.w,
                tex.id,
                { pos.x, pos.y},
                { pos.x + widthHeight.x, pos.y + widthHeight.y},
                {uv.x,uv.y},
                {uv.z,uv.w}
            );
    return isDropped;

}