#pragma once
#include "World/WorldDefinitions.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "raylib.h"

#define MAX_COLUMNS 20

namespace World {
class TestMap {
public:
  TestMap();
  void Update(Entities::Player *player, Entities::Enemy *enemy);
  void Draw(Entities::Player *player);
  BoundingBox GetPlaneBoundingBox();

private:
  float heights[MAX_COLUMNS];
  Vector3 positions[MAX_COLUMNS];
  Color colors[MAX_COLUMNS];
  Color tempColors[MAX_COLUMNS];
  BoundingBox boundingBox[MAX_COLUMNS];
  Plane plane;
  Cube leftWall;
  Cube backWall;
  Cube rightWall;
};
} // namespace World
