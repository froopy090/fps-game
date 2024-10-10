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
      sprites(sprites) {}

void Weapon::Event() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    source = sprites.firingRec;
    timer.Start(1.0f);
    std::cout << "Gun fired!" << std::endl;
  }
}

void Weapon::Update(){
    timer.Update();
    if(timer.Finished()){
        source = sprites.idleRec;
    }
}
} // namespace Game
