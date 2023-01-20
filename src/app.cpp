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
        game->AddToTexlist( 0, 0, resources.titleBackground.id, {0,0}, {windowWidth, windowHeight}, {0,0}, {1,1});
        game->AddToTexlist( 10, 0, resources.title.id,
                { (float)windowWidth/2.f - resources.title.width/2.f, (float)64},
                { (float)windowWidth/2.f + resources.title.width/2.f, (float)64+resources.title.height},
                {0.f,0.f},                           
                {1.f,1.f});
        if (ui->Button(game, resources.newGame, {windowWidth/2 - 100, windowHeight/2 - 50}, 200, 100, {1,1,1,0.5}) ||
            ImGui::IsKeyPressed(ImGuiKey_Enter, false))
            scene = SCENE_GAME;
        break;

    case SCENE_GAME:
    {
        game->LevelUpdate(EntityList, tilemap, resources, &scene, &restart);
        tilemap->Update(game, resources);
        ui->Update(*imdrawlist, resources, game, EntityList /*entity,*/, *tilemap);
        
        for (std::vector<Entity*>::iterator it = EntityList.begin(); it != EntityList.end(); )
        {
            Entity* e = *it;
            if (e->GetLife() <= 0 && e->GetType() == 1)
            {
                switch (e->GetClassType())
                {
                    case 0:
                        game->money += WIMP_DROP; break;
                    case 1:
                        game->money += BEEFY_DROP; break;
                    case 2:
                        game->money += HEALER_DROP; break;
                }
                it = EntityList.erase(it);
                delete e;
            }
            else
            {
                it++;
            }
        }
        for(size_t i = 0; i<EntityList.size(); i++)
        { 
            EntityList[i]->Update(EntityList, game);
            EntityList[i]->Draw(game, resources, i);
            EntityList[i]->Movement(*tilemap);
        }
        break;
    }
        
    
    default:
        break;
    }
    if (restart)
    {
        delete game;
        game = new Game();
        restart = false;
    }
    game->TexlistUpdate(*imdrawlist);
}
