#pragma once

#include <Entity.h>
#include <raylib.h>
#include <vector>

struct CollisionInfo {
  bool collided;
  enum class Direction { NONE, TOP, BOTTOM, LEFT, RIGHT, UP, DOWN } direction;
  enum class Axis { NONE, X, Y, Z } axis;
  BoundingBox box1;
  BoundingBox box2;
  Entity entity1;
  Entity entity2;
};

struct CollisionBuffer {
  std::vector<CollisionInfo> collisions;
};
