#pragma once
#include "raylib.h"
#include <vector>

namespace Game {
class Entity2D {
public:
  Entity2D(Texture2D texture, Rectangle source, Rectangle destination,
           Vector2 origin, float rotation);
  virtual ~Entity2D();
  virtual void Event();
  virtual void Update();
  virtual void Draw();

protected:
  Texture2D texture;
  Rectangle source;
  Rectangle destination;
  Vector2 origin;
  float rotation;
};
} // namespace Game
