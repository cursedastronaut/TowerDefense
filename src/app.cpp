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
    ui->Update(*imdrawlist, resources);
    
}
