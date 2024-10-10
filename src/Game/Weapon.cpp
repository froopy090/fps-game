#include "Game/Weapon.h"
#include "Game/Entity2D.h"
#include "iostream"
#include <cmath>
#include <raylib.h>

namespace Game {
Weapon::Weapon(Texture2D texture, SpriteSourceRec sprites,
               Rectangle destination, Vector2 origin, float rotation)
    : Game::Entity2D(texture, sprites.idleRec, destination, origin, rotation),
      sprites(sprites) {}

void Weapon::Event() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    source = sprites.firingRec;
    std::cout << "Gun fired!" << std::endl;
  } else {
    source = sprites.idleRec;
  }
}
} // namespace Game
