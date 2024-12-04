#pragma once
#include "Entities/Player.h"
#include "World/BaseObjects.h"
#include "World/LargeColumn.h"
#include "World/Stairs.h"
#include <vector>

namespace Utility {
class WorldObjectManager {
public:
  WorldObjectManager(Entities::Player *player);
  void AddObject(int objectID, Vector3 position);
  void Draw();

private:
  // object vectors
  std::vector<World::Plane> planes;
  std::vector<World::Cube> cubes;
  std::vector<World::LargeColumn> columns;
  std::vector<World::Stairs> stairs;

  // other stuff needed
  Entities::Player *player;
};
} // namespace Utility
