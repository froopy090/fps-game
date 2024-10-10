#pragma once
#include "Entity2D.h"
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

private:
  SpriteSourceRec sprites;
};
} // namespace Game
