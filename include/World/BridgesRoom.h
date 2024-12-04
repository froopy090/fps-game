#pragma once

#include "Entities/Player.h"
#include "Utility/EnemyManager.h"
#include "World/BaseObjects.h"
#include "World/LargeColumn.h"
#include "World/Stairs.h"
#include "World/WorldDefinitions.h"
#include "vector"

namespace World {
class BridgesRoom {
public:
  BridgesRoom(Entities::Player *player, Utility::EnemyManager *enemyManager);
  void Update();
  void Draw();

  // Returns a reference to the roomMatrix
  const int (&GetRoomMatrix())[ROOM_SIZE][ROOM_SIZE];

private:
  static const int roomMatrix[ROOM_SIZE][ROOM_SIZE];
  static const int heightMatrix[ROOM_SIZE][ROOM_SIZE];
  std::vector<Plane> floors;
  std::vector<Cube> walls;
  std::vector<LargeColumn> columns;
  std::vector<Stairs> stairs;
  Entities::Player *playerPtr;
  Utility::EnemyManager *enemyManagerPtr;

  // Helper functions
  void Reset(Entities::Player *player, Utility::EnemyManager *enemyManager);

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
} // namespace World
