#pragma once
#include "Entities/Player.h"
#include "Utility/EnemyManager.h"
#include "Utility/WorldObjectManager.h"
#include "World/Room.h"
#include "World/Stairs.h"
#include "World/WorldDefinitions.h"
#include "vector"

namespace World {
class Room002 : Room {
public:
  Room002(Entities::Player *player, Utility::EnemyManager *enemyManager,
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
};
} // namespace World
