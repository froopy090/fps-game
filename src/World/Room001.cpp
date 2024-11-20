#include "World/Room001.h"
#include "Entities/Enemy.h"
#include "Entities/EntityDefinitions.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "World/BaseObjects.h"
#include "World/Stairs.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <math.h>
#include <vector>

// Helper Functions -------------------------------------------------------
//
// resets necessary player and enemy variables
void Reset(Entities::Player *player, Entities::Enemy *enemy) {
  // Reset
  player->SetPlaneCollision(false);
  enemy->SetPlaneCollision(false);
}

template <typename Object>
void CheckCollisionObjects(Entities::Player *player, Entities::Enemy *enemy,
                           std::vector<Object> objects) {
  for (Object &obj : objects) {
    if (Utility::EntityCollisionObject(player, &obj)) {
      Utility::LockEntityAxis(player, &obj);
    }
    if (Utility::EntityCollisionObject(enemy, &obj)) {
      Utility::LockEntityAxis(enemy, &obj);
    }
  }
}

void CheckStairsCollision(Entities::Player *player, Entities::Enemy *enemy,
                          std::vector<World::Stairs> stairs) {
  // Checks collision between stairs and entities
  for (World::Stairs &stair : stairs) {
    World::Cube stairWall = stair.GetStairWall();
    if (Utility::EntityCollisionObject(player, &stairWall)) {
      Utility::LockEntityAxis(player, &stairWall);
    }
    if (Utility::EntityCollisionObject(enemy, &stairWall)) {
      Utility::LockEntityAxis(enemy, &stairWall);
    }
    std::vector<World::Cube> stairCubes = stair.GetCubeVector();
    for (World::Cube &stairCube : stairCubes) {
      if (Utility::EntityCollisionObject(player, &stairCube)) {
        Utility::LockEntityAxis(player, &stairCube);
      }
      if (Utility::EntityCollisionObject(enemy, &stairCube)) {
        Utility::LockEntityAxis(enemy, &stairCube);
      }
    }
  }
}

// checks if enemy vision is blocked by an object
template <typename Object>
void CheckEnemyVision(Entities::Player *player, Entities::Enemy *enemy,
                      std::vector<Object> &objects) {
  for (Object &obj : objects) {
    // finding one wall where the vision ray collides
    if (!Utility::CanSeeTarget(enemy, player, &obj)) {
      if (enemy->GetState() != Entities::ENEMY_IDLE) {
        enemy->SetIdle();
        break;
      }
    }
  }
}

void CheckEnemyVisionStairs(Entities::Player *player, Entities::Enemy *enemy,
                            std::vector<World::Stairs> &stairs) {
  for (World::Stairs &stair : stairs) {
    World::Cube stairWall = stair.GetStairWall();
    if (!Utility::CanSeeTarget(enemy, player, &stairWall) &&
        enemy->GetState() != Entities::ENEMY_IDLE) {
      enemy->SetIdle();
      break;
    }
  }
}
// End Helper Functions --------------------------------------------------------
//
namespace World {
const int Room001::roomMatrix[ROOM_SIZE][ROOM_SIZE] = {
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Room001::Room001() {
  // Calculate center of matrix
  int center = ROOM_SIZE / 2;

  // Populate floors and walls
  for (int i = 0; i < ROOM_SIZE; i++) {
    for (int j = 0; j < ROOM_SIZE; j++) {
      // calulating position of tile
      float x = (i - center) * (-TILE_SIZE);
      float z = (j - center) * (-TILE_SIZE);
      Vector3 position = {x, 0.0f, z};

      if (roomMatrix[i][j] == 0) {
        floors.emplace_back(position);
      } else if (roomMatrix[i][j] == 1) {
        walls.emplace_back(position);
      } else if (roomMatrix[i][j] == 2) {
        columns.emplace_back(position);
      } else if (roomMatrix[i][j] == 3) {
        stairs.emplace_back(position);
      }
    }
  }
}

void Room001::Update(Entities::Player *player, Entities::Enemy *enemy) {
  Reset(player, enemy);

  // Collision checks
  CheckCollisionObjects(player, enemy, floors);
  CheckCollisionObjects(player, enemy, walls);
  CheckCollisionObjects(player, enemy, columns);
  CheckStairsCollision(player, enemy, stairs);

  // Enemy vision checks
  CheckEnemyVision(player, enemy, walls);
  CheckEnemyVision(player, enemy, columns);
  CheckEnemyVisionStairs(player, enemy, stairs);
}

void Room001::Draw() {
  for (Plane &floor : floors) {
    floor.Draw();
  }
  for (Cube &wall : walls) {
    wall.Draw();
  }
  for (LargeColumn &column : columns) {
    column.Draw();
  }
  for (Stairs &stair : stairs) {
    stair.Draw();
  }
}

} // namespace World
