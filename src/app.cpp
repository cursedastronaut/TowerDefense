
#include "app.hpp"

#include "imgui_utils.hpp"

App::App()
{
    //App::tilemap = new Tilemap();
 
}

App::~App()
{
}

void App::Update()
{
    imdrawlist = ImGui::GetBackgroundDrawList();

    tilemap->tilemapUpdate();
    imdrawlist->AddImage(resources.Mario.id, {16,20}, {100,100}, {0,0}, {1,1});
}
