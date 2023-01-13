#include "app.hpp"
#include "constants.hpp"
#include "imgui_utils.hpp"
#include "tilemap.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "UI.hpp"

App::App()
{
    this->tilemap = new Tilemap();
    this->game = new Game();

    
}

App::~App()
{
}

void App::Update()
{
    imdrawlist = ImGui::GetBackgroundDrawList();
    io = &ImGui::GetIO();
    deltaTime = io->DeltaTime;
    ImGui::Text("FPS: %0.f", 1/deltaTime);
    switch (scene)
    {
    case SCENE_TITLE:
        game->AddToTexlist( 10, 0, resources.title.id,
                { (float)windowWidth/2.f - resources.title.width/2.f, (float)64},
                { (float)windowWidth/2.f + resources.title.width/2.f, (float)64+resources.title.height},
                {0.f,0.f},                           
                {1.f,1.f});
        if (ui->Button(*imdrawlist, resources.newGame, {windowWidth/2 - 100, windowHeight/2 - 50}, 200, 100, {1,1,1,0.5}) ||
            ImGui::IsKeyPressed(ImGuiKey_Enter, false))
            scene = SCENE_GAME;
        /*game->AddToTexlist( 20, resources.newGame.id,
                {windowWidth/2 - 100, windowHeight/2 - 50},
                {windowWidth/2 + 100, windowHeight/2 + 50},
                {0,0},                           
                {1,1});*/
        break;

    case SCENE_GAME:
    {
        game->LevelUpdate(EntityList, tilemap);
        tilemap->Update(game, resources);
        ui->Update(*imdrawlist, resources, game, EntityList /*entity,*/, *tilemap);
        
        
        for(size_t i = 0; i<EntityList.size(); i++)
        {
            EntityList[i]->Update(EntityList);
            EntityList[i]->Draw(game, resources, i);
            EntityList[i]->Movement(*tilemap);
        }
        //entity->Update(game, resources, *tilemap);
        break;
    }
        
    
    default:
        break;
    }
    game->TexlistUpdate(*imdrawlist);
}
