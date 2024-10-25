#pragma once
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "raylib.h"

#define MAX_COLUMNS 20

namespace World {
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

inline BoundingBox InitCubeBoundingBox(Cube c) {
  BoundingBox bb;
  bb.min = (Vector3){c.position.x - c.size.x / 2.0f, 0.0f,
                     c.position.z - c.size.z / 2.0f};
  bb.max = (Vector3){c.position.x + c.size.x / 2.0f, c.size.y,
                     c.position.z + c.size.z / 2.0f};
  return bb;
}

inline BoundingBox InitPlaneBoundingBox(Plane p) {
  BoundingBox bb;
  bb.min =
      (Vector3){-p.dimension.x / 2.0f, p.position.y, -p.dimension.y / 2.0f};
  bb.max = (Vector3){p.dimension.x / 2.0f, p.position.y, p.dimension.y / 2.0f};
  return bb;
}

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
