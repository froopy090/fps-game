#pragma once
#include "raylib.h"
#include "World/WorldDefinitions.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"

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
