#pragma once
#include "Entities/Player.h"
#include "Utility/EnemyManager.h"
#include "Utility/WorldObjectManager.h"
#include "World/Stairs.h"
#include "World/WorldDefinitions.h"
#include "vector"
#include "World/Room.h"

namespace World {
class Room001 : public Room{
public:
  Room001(Entities::Player *player, Utility::EnemyManager *enemyManager,
          Utility::WorldObjectManager *objectManager);
  void Update() override;
  void Draw() override;

  // Returns a reference to the roomMatrix
  const int (&GetRoomMatrix())[ROOM_SIZE][ROOM_SIZE];

private:
  static const int roomMatrix[ROOM_SIZE][ROOM_SIZE];
  static const int heightMatrix[ROOM_SIZE][ROOM_SIZE];
  Utility::WorldObjectManager *objectManager;
  Entities::Player *playerPtr;
  Utility::EnemyManager *enemyManagerPtr;

  // Helper functions
  void Reset(Entities::Player *player, Utility::EnemyManager *enemyManager);
};
} // namespace World
