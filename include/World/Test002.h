#pragma once
#include "raylib.h"
//#include "World/WorldDefinitions.h"
#include "World/Plane.h"
#include "World/Cube.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"

namespace World {
class Test002 {
public:
  Test002();
  void Update(Entities::Player *player, Entities::Enemy *enemy);
  void Draw(Entities::Player *player);
  BoundingBox GetPlaneBoundingBox();
  bool CheckPlaneCollisionPlayer(BoundingBox playerBox);

private:
  Plane floor;
  Cube leftWall, backWall, rightWall; 
  Cube cube;
};
} // namespace World
