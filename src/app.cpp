#include "app.hpp"
#include "constants.hpp"
#include "imgui_utils.hpp"

App::App()
{
    this->tilemap = new Tilemap();
    this->game = new Game();
    this->entity = new Entity(*tilemap);
    this->io = new ImGuiIO();
}

App::~App()
{
}

void App::Update()
{
    imdrawlist = ImGui::GetBackgroundDrawList();
    deltaTime = io->DeltaTime;
    ImGui::Text("FPS: %0.f", 1/deltaTime);
    switch (scene)
    {
    case SCENE_TITLE:
        game->AddToTexlist( 10, resources.title.id,
                { windowWidth/2 - resources.title.width/2, 64},
                { windowWidth/2 + resources.title.width/2, 64+resources.title.height},
                {0,0},                           
                {1,1});
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
        tilemap->Update(game, resources);
        ui->Update(*imdrawlist, resources, game, entity, *tilemap);
        entity->Update(game, resources, *tilemap);
        break;
    
    default:
        break;
    }
    game->TexlistUpdate(*imdrawlist);
}

void Game::TexlistUpdate(ImDrawList& dl)
{
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        if (arrayTexlist[i].active)
        {
            switch (arrayTexlist[i].type)
            {
            case 0:
                dl.AddImage(
                    arrayTexlist[i].id,
                    arrayTexlist[i].posUL,
                    arrayTexlist[i].posBR,
                    arrayTexlist[i].uvUL,
                    arrayTexlist[i].uvBR
                );
                break;
            case 1:
                dl.AddRectFilled(
                    arrayTexlist[i].posUL,
                    arrayTexlist[i].posBR,
                    arrayTexlist[i].col,
                    arrayTexlist[i].round
                );
                break;
            case 2:
                dl.AddRect(
                    arrayTexlist[i].posUL,
                    arrayTexlist[i].posBR,
                    arrayTexlist[i].col,
                    arrayTexlist[i].round,
                    0,
                    arrayTexlist[i].thick
                );
                break;
            case 3:
                dl.AddText(
                    arrayTexlist[i].posUL,
                    arrayTexlist[i].col,
                    arrayTexlist[i].text,
                    NULL
                );
            default:
                break;
            }
            arrayTexlist[i].active = false;
        }
    }
}

void Game::AddToTexlist(int z, ImTextureID id, ImVec2 posUL, ImVec2 posBR, ImVec2 uvUL, ImVec2 uvBR)
{
    arrayTexlist[z].active  = true;
    arrayTexlist[z].type    = 0;
    arrayTexlist[z].id      = id;
    arrayTexlist[z].posUL   = posUL;
    arrayTexlist[z].posBR   = posBR;
    arrayTexlist[z].uvUL    = uvUL;                          
    arrayTexlist[z].uvBR    = uvBR;
    arrayTexlist[z].col     = 0;
}

void Game::AddRectFilledTexlist(int z, ImVec2 posUL, ImVec2 posBR, ImU32 col, float rounding)
{
    arrayTexlist[z].active  = true;
    arrayTexlist[z].posUL   = posUL;
    arrayTexlist[z].posBR   = posBR;
    arrayTexlist[z].col     = col;
    arrayTexlist[z].type    = 1;
    arrayTexlist[z].round   = rounding;
}

void Game::AddRectTexlist(int z, ImVec2 posUL, ImVec2 posBR, ImU32 col, float rounding, float thickness)
{
    arrayTexlist[z].active  = true;
    arrayTexlist[z].posUL   = posUL;
    arrayTexlist[z].posBR   = posBR;
    arrayTexlist[z].col     = col;
    arrayTexlist[z].type    = 2;
    arrayTexlist[z].round   = rounding;
    arrayTexlist[z].thick   = thickness;
}

void Game::AddTextTexlist(int z, ImVec2 pos, ImU32 col, const char *text)
{
    arrayTexlist[z].active  = true;
    arrayTexlist[z].posUL   = pos;
    arrayTexlist[z].text    = text;
    arrayTexlist[z].col     = col;
    arrayTexlist[z].type    = 3;
}