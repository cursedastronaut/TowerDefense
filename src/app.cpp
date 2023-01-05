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

    
    switch (scene)
    {
    case SCENE_TITLE:
    imdrawlist->AddImage(resources.title.id,
                { windowWidth/2 - resources.title.width/2, 64},
                { windowWidth/2 + resources.title.width/2, 64+resources.title.height},
                {0,0},                           
                {1,1});
        if (ui->Button(*imdrawlist, resources.Void, {windowWidth/2 - 100, windowHeight/2 - 50}, 200, 100, {1,1,1,0.5}) ||
            ImGui::IsKeyPressed(ImGuiKey_Enter, false))
            scene = SCENE_GAME;
        
        break;

    case SCENE_GAME:
        tilemap->Update(*imdrawlist, resources);
        ui->Update(*imdrawlist, resources);
        break;
    
    default:
        break;
    }
}
