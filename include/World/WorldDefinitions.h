#pragma once
#include "raylib.h"

namespace World {
constexpr int TILE_SIZE = 10;
constexpr int WALL_HEIGHT = 10;
constexpr int MAP_SIZE = 10;

struct Plane {
  Vector3 position;
  Vector2 dimension;
  Color color;
  BoundingBox boundingBox;
};

struct Cube {
  Vector3 position;
  Vector3 size;
  Color color;
  BoundingBox boundingBox;
};
} // namespace World
