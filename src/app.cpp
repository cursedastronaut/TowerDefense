#include "app.hpp"
#include "constants.hpp"
#include "imgui_utils.hpp"

App::App()
{
    this->tilemap = new Tilemap();
    this->game = new Game();
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
        game->AddToTexlist( 10, 0, resources.title.id,
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
        ui->Update(*imdrawlist, resources, game, EntityList /*entity,*/, *tilemap);
        
        for(size_t i = 0; i<EntityList.size(); i++)
        {
            EntityList[i]->Update(game, resources, *tilemap);
            EntityList[i]->Draw(game, resources, i);
        }

        //entity->Update(game, resources, *tilemap);

        break;
    
    default:
        break;
    }
    game->TexlistUpdate(*imdrawlist);
}

void Game::TexlistUpdate(ImDrawList& dl)
{
    for (int layer = 0; layer < 32; layer++)
    {
        for (int z = 0; z < MAX_TEXTURES; z++)
        {
            if (arrayTexlist[layer][z].active)
            {
                switch (arrayTexlist[layer][z].type)
                {
                case 0:
                    dl.AddImage(
                        arrayTexlist[layer][z].id,
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].posBR,
                        arrayTexlist[layer][z].uvUL,
                        arrayTexlist[layer][z].uvBR
                    );
                    break;
                case 1:
                    dl.AddRectFilled(
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].posBR,
                        arrayTexlist[layer][z].col,
                        arrayTexlist[layer][z].round
                    );
                    break;
                case 2:
                    dl.AddRect(
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].posBR,
                        arrayTexlist[layer][z].col,
                        arrayTexlist[layer][z].round,
                        0,
                        arrayTexlist[layer][z].thick
                    );
                    break;
                case 3:
                    dl.AddText(
                        arrayTexlist[layer][z].posUL,
                        arrayTexlist[layer][z].col,
                        arrayTexlist[layer][z].text,
                        NULL
                    );
                default:
                    break;
                }
                arrayTexlist[layer][z].active = false;
            }
        }
    }
}

void Game::AddToTexlist(int z, int layer, ImTextureID id, ImVec2 posUL, ImVec2 posBR, ImVec2 uvUL, ImVec2 uvBR)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].type    = 0;
    arrayTexlist[layer][z].id      = id;
    arrayTexlist[layer][z].posUL   = posUL;
    arrayTexlist[layer][z].posBR   = posBR;
    arrayTexlist[layer][z].uvUL    = uvUL;                          
    arrayTexlist[layer][z].uvBR    = uvBR;
    arrayTexlist[layer][z].col     = 0;
}

void Game::AddRectFilledTexlist(int z, int layer, ImVec2 posUL, ImVec2 posBR, ImU32 col, float rounding)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = posUL;
    arrayTexlist[layer][z].posBR   = posBR;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 1;
    arrayTexlist[layer][z].round   = rounding;
}

void Game::AddRectTexlist(int z, int layer, ImVec2 posUL, ImVec2 posBR, ImU32 col, float rounding, float thickness)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = posUL;
    arrayTexlist[layer][z].posBR   = posBR;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 2;
    arrayTexlist[layer][z].round   = rounding;
    arrayTexlist[layer][z].thick   = thickness;
}

void Game::AddTextTexlist(int z, int layer, ImVec2 pos, ImU32 col, const char *text)
{
    arrayTexlist[layer][z].active  = true;
    arrayTexlist[layer][z].posUL   = pos;
    arrayTexlist[layer][z].text    = text;
    arrayTexlist[layer][z].col     = col;
    arrayTexlist[layer][z].type    = 3;
}