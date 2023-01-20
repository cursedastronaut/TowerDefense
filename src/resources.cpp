#include "resources.hpp"

Resources::Resources()
{
   //Tilesets
   tilesetWood    =  ImGuiUtils::LoadTexture("assets/textures/tilesets/wood.png", true);
   tilesetCastle  =  ImGuiUtils::LoadTexture("assets/textures/tilesets/castle.png", true);
   tilesetPath    =  ImGuiUtils::LoadTexture("assets/textures/tilesets/path.png", true);

   //Entities
   Turret         =  ImGuiUtils::LoadTexture("assets/textures/characters/tower.png", true);
   Fighter3       =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter03.png", true);
   Fighter4       =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter04.png", true);
   Fighter5       =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter05.png", true);
   Fighter3Frozen =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter03_frozen.png", true);
   Fighter4Frozen =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter04_frozen.png", true);
   Fighter5Frozen =  ImGuiUtils::LoadTexture("assets/textures/characters/fighter05_frozen.png", true);

   //Title screen
   Void           =  ImGuiUtils::LoadTexture("assets/textures/void.png", true);
   title          =  ImGuiUtils::LoadTexture("assets/textures/title.png", true);
   newGame        =  ImGuiUtils::LoadTexture("assets/textures/new_game.png", true);
   gameOver       =  ImGuiUtils::LoadTexture("assets/textures/game_over.png", true);
   titleBackground=  ImGuiUtils::LoadTexture("assets/textures/background.png", true);
}