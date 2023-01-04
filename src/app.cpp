#include "app.hpp"
#include "constants.hpp"
#include "imgui_utils.hpp"

App::App()
{
    this->tilemap = new Tilemap();
}

App::~App()
{
}

void App::Update()
{
    imdrawlist = ImGui::GetBackgroundDrawList();

    tilemap->Update(*imdrawlist, resources);
    //imdrawlist->AddImage(resources.tileset.id, {0,0}, {32,32}, {0,0}, {TILE_HUV,TILE_VUV});
    //idrawlist->AddImage(resources.Mario.id, {16,20}, {100,100}, {0,0}, {1,1});
    
}
