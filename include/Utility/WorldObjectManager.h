#pragma once
#include "Entities/Player.h"
#include "Utility/EnemyManager.h"
#include "World/BaseObjects.h"
#include "World/LargeColumn.h"
#include "World/Stairs.h"
#include <vector>

namespace Utility {
class WorldObjectManager {
public:
  WorldObjectManager(Entities::Player *player, EnemyManager *enemyManager);
  void AddObject(int objectID, Vector3 position);
  void Update();
  void Draw();

private:
  // object vectors
  std::vector<World::Plane> planes;
  std::vector<World::Cube> cubes;
  std::vector<World::LargeColumn> columns;
  std::vector<World::Stairs> stairs;

  // other stuff needed
  Entities::Player *player;
  EnemyManager *enemyManager;

  // Helper functions
  template <typename Object>
  void CheckCollisionObjects(Entities::Player *player,
                             Utility::EnemyManager *enemyManager,
                             std::vector<Object> objects);
  void CheckStairsCollision(Entities::Player *player,
                            Utility::EnemyManager *enemyManager,
                            std::vector<World::Stairs> stairs);

  template <typename Object>
  void CheckEnemyVision(Entities::Player *player,
                        Utility::EnemyManager *enemyManager,
                        std::vector<Object> &objects);

  void CheckEnemyVisionStairs(Entities::Player *player,
                              Utility::EnemyManager *enemyManager,
                              std::vector<World::Stairs> &stairs);
};
} // namespace Utility
