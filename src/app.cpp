#include "app.hpp"
#include "constants.hpp"
#include "imgui_utils.hpp"
#include "tilemap.hpp"
#include "game.hpp"
#include "entity.hpp"
#include "UI.hpp"

//Executed once on program launch
App::App()
{
    //Creates tilemap and game
    this->tilemap = new Tilemap();
    this->game = new Game();
}

App::~App()
{
}

void App::Update()
{
    //Creates the drawlist
    imdrawlist = ImGui::GetBackgroundDrawList();
    io = &ImGui::GetIO();
    deltaTime = io->DeltaTime;

    ImGui::Text("FPS: %0.f", 1/deltaTime);

    //Scene processing
    switch (scene)
    {
    //Title screen processing
    case SCENE_TITLE:
        //Draws background
        game->AddToTexlist( 0, 0, resources.titleBackground.id, {0,0}, {windowWidth, windowHeight}, {0,0}, {1,1});
        //Draws game logo
        game->AddToTexlist( 10, 0, resources.title.id,
                { (float)windowWidth/2.f - resources.title.width/2.f, (float)64},
                { (float)windowWidth/2.f + resources.title.width/2.f, (float)64+resources.title.height},
                {0.f,0.f},{1.f,1.f});
        //Draws the Button to play.
        if (ui->Button(game, resources.newGame, {windowWidth/2 - 100, windowHeight/2 - 50}, 200, 100, {1,1,1,0.5}) ||
            ImGui::IsKeyPressed(ImGuiKey_Enter, false))
            scene = SCENE_GAME;
        //Draws the version number
        game->AddTextTexlist(20, 0, {0 , windowHeight - 16}, 0xFF000000, VERSION);
        break;

    //Game processing
    case SCENE_GAME:
    {
        //Updates everything Level related (enemy spawn, gameover...)
        game->LevelUpdate(EntityList, tilemap, resources, &scene, &restart);
        //Draws the tilemap
        tilemap->Update(game, resources);
        //Draws and process the UI
        ui->Update(*imdrawlist, resources, game, EntityList /*entity,*/, *tilemap);
        
        //Looping through every entity
        for (std::vector<Entity*>::iterator it = EntityList.begin(); it != EntityList.end(); )
        {
            Entity* e = *it;
            //If enemy is dead
            if (e->life <= 0 && e->GetType() == 1)
            {
                //Give money depending on what type of enemy it was
                switch (e->GetClassType())
                {
                    case 0:
                        game->money += WIMP_DROP; break;
                    case 1:
                        game->money += BEEFY_DROP; break;
                    case 2:
                        game->money += HEALER_DROP; break;
                }
                //Removes the enemy from the Entity list
                it = EntityList.erase(it);
                delete e;
            }
            else
            {
                it++;
            }
        }
        //Loops through every entity
        for(size_t i = 0; i<EntityList.size(); i++)
        { 
            //Entity processing
            EntityList[i]->Update(EntityList, game);
            EntityList[i]->Draw(game, resources, i);
            EntityList[i]->Movement(*tilemap);
        }
        break;
    }
        
    
    default:
        break;
    }
    //After a gameover, this will be executed once.
    if (restart)
    {
        delete game;
        game = new Game();
        restart = false;
    }
    game->TexlistUpdate(*imdrawlist);
}
