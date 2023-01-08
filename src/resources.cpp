#include "resources.hpp"

Resources::Resources()
{
   //Tilesets
   tilesetWood    =  ImGuiUtils::LoadTexture("assets/textures/tilesets/wood.png", true);
   tilesetCastle  =  ImGuiUtils::LoadTexture("assets/textures/tilesets/castle.png", true);
   tilesetPath    =  ImGuiUtils::LoadTexture("assets/textures/tilesets/path.png", true);

   Turret          =  ImGuiUtils::LoadTexture("assets/textures/characters/tower.png", true);
   Fighter4       =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter04.png", true);
   Void           =  ImGuiUtils::LoadTexture("assets/textures/void.png", true);
   title          =  ImGuiUtils::LoadTexture("assets/textures/title.png", true);
   newGame        =  ImGuiUtils::LoadTexture("assets/textures/new_game.png", true);
}