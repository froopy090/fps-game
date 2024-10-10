#pragma once
#include "Entity2D.h"
#include "Utility/Timer.h"
#include <raylib.h>

namespace Game {
struct SpriteSourceRec {
  Rectangle idleRec;
  Rectangle firingRec;
};

class Weapon : public Entity2D {
public:
  Weapon(Texture2D texture, SpriteSourceRec source, Rectangle destination,
         Vector2 origin, float rotation);

  void Event() override;

  void Update() override;

private:
  SpriteSourceRec sprites;
  Utility::Timer timer;
};
} // namespace Game
