#pragma once

#include <raylib.h>
#include <vector>

struct CollisionInfo {
  bool collided;
  enum class Direction { NONE, TOP, BOTTOM } direction;
  enum class Axis { X, Y, Z } axis;
  BoundingBox box1;
  BoundingBox box2;
};

struct CollisionBuffer {
  std::vector<CollisionInfo> collisions;
};
