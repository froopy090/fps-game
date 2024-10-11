#include "Game/Weapon.h"
#include "Game/Entity2D.h"
#include "Utility/Timer.h"
#include "iostream"
#include <cmath>
#include <raylib.h>

namespace Game {
Weapon::Weapon(Texture2D texture, SpriteSourceRec sprites,
               Rectangle destination, Vector2 origin, float rotation)
    : Game::Entity2D(texture, sprites.idleRec, destination, origin, rotation),
      sprites(sprites), state(IDLE) {}

void Weapon::Event() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    timer.Start(0.5f);
    std::cout << "Gun fired!" << std::endl;
  }
}

void Weapon::Update() {
  timer.Update();
  if (timer.Finished()) {
    state = IDLE;
    source = sprites.idleRec;
  } else {
    state = FIRING;
    source = sprites.firingRec2;
  }
}
} // namespace Game
