#pragma once
#include "World/Cube.h"
#include "World/Plane.h"
#include "World/WorldDefinitions.h"
#include "vector"

namespace World {
class Room001 {
public:
  Room001();
  void Draw();

private:
  static const int roomMatrix[ROOM_SIZE][ROOM_SIZE];
  // TODO: implement the height map
  // static const int heightMatrix[ROOM_SIZE][ROOM_SIZE];
  std::vector<Plane> floors;
  std::vector<Cube> walls;
};
} // namespace World
