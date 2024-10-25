#pragma once
#include "World/TestMap.h"
#include "raylib.h"

namespace World {
class Test002 {
public:
  Test002();
  void Update(Entities::Player *player, Entities::Enemy *enemy);
  void Draw(Entities::Player *player);
  BoundingBox GetPlaneBoundingBox();

private:
  Plane floor;
  Cube leftWall;
  Cube backWall;
  Cube rightWall;
  Cube cube;
};
} // namespace World
