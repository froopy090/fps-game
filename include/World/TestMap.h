#pragma once
#include "raylib.h"
#include "Entities/Player.h"

#define MAX_COLUMNS 20

namespace World {
class TestMap {
public:
  TestMap();
  void Draw(Entities::Player *player);
private:
  float heights[MAX_COLUMNS];
  Vector3 positions[MAX_COLUMNS];
  Color colors[MAX_COLUMNS];
};
} // namespace World
