#include "resources.hpp"

Resources::Resources()
{
   Mario = ImGuiUtils::LoadTexture("assets/mario.png", true);
   tileset = ImGuiUtils::LoadTexture("assets/textures/tilesets/wood.png", true);
}