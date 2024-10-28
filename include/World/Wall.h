#pragma once
#include "raylib.h"

namespace World {
class Wall {
public:
  Wall(Vector3 position);
  void Draw();

private:
  Vector3 position;
  Vector3 dimensions;
  Color color;
  BoundingBox box;
};
} // namespace World
