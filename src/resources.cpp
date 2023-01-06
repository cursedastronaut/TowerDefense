#include "resources.hpp"

Resources::Resources()
{
   //Mario    =  ImGuiUtils::LoadTexture("assets/mario.png", true);
   tilesetWood    =  ImGuiUtils::LoadTexture("assets/textures/tilesets/wood.png", true);
   tilesetCastle  =  ImGuiUtils::LoadTexture("assets/textures/tilesets/castle.png", true);
   Tower          =  ImGuiUtils::LoadTexture("assets/textures/characters/tower.png", true);
   Fighter4       =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter04.png", true);
   Void           =  ImGuiUtils::LoadTexture("assets/textures/void.png", true);
   title          =  ImGuiUtils::LoadTexture("assets/textures/title.png", true);
}