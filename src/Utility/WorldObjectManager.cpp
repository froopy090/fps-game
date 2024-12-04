#include "Utility/WorldObjectManager.h"

namespace Utility {
WorldObjectManager::WorldObjectManager(Entities::Player *player)
    : player(player) {}

void WorldObjectManager::AddObject(int objectID, Vector3 position) {
  switch (objectID) {
  case 0:
    planes.emplace_back(position);
    break;
  case 1:
    cubes.emplace_back(position);
    break;
  case 2:
    columns.emplace_back(position);
    break;
  case 3:
    stairs.emplace_back(position);
    break;
  }
}

void WorldObjectManager::Draw() {
  BeginMode3D(player->camera);
  for (World::Plane &plane : planes) {
    plane.Draw();
  }
  for (World::Cube &cube : cubes) {
    cube.Draw();
  }
  for (World::LargeColumn &column : columns) {
    column.Draw();
  }
  for (World::Stairs &stair : stairs) {
    stair.Draw();
  }
  EndMode3D();
}
} // namespace Utility
