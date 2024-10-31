#pragma once
#include "Entities/Player.h"
#include "World/LargeColumn.h"
#include "World/BaseObjects.h"
#include "World/WorldDefinitions.h"
#include "vector"

namespace World {
class Room001 {
public:
  Room001();
  void Update(Entities::Player *player);
  void Draw();

private:
  static const int roomMatrix[ROOM_SIZE][ROOM_SIZE];
  // TODO: implement the height map
  // static const int heightMatrix[ROOM_SIZE][ROOM_SIZE];
  std::vector<Plane> floors;
  std::vector<Cube> walls;
  std::vector<LargeColumn> columns;
};
} // namespace World
