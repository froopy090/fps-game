#include "World/BridgesRoom.h"
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

// Helper Functions ------------------------------------------------------
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
// End Helper functions ---------------------------------------------------
//
namespace World {
const int BridgesRoom::roomMatrix[ROOM_SIZE][ROOM_SIZE] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {1, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 1, 1, 1, 2, 2, 0, 2, 2, 0, 2, 2, 0, 0, 1, 0, 3, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 3, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

const int BridgesRoom::heightMatrix[ROOM_SIZE][ROOM_SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

BridgesRoom::BridgesRoom(Entities::Player *player,
                         Utility::EnemyManager *enemyManager)
    : playerPtr(player), enemyManagerPtr(enemyManager) {
  // Calculate center of matrix
  int center = ROOM_SIZE / 2;

  float randomValue = 0.0f;

  // Populate map and spawn enemies
  for (int i = 0; i < ROOM_SIZE; i++) {
    for (int j = 0; j < ROOM_SIZE; j++) {
      // calulating position of tile
      float x = (i - center) * (-TILE_SIZE);
      float y = (float)heightMatrix[i][j];
      float z = (j - center) * (-TILE_SIZE);
      Vector3 position = {x, y, z};

      // generating random value
      randomValue = GetRandomValue(0, 1);

      if (roomMatrix[i][j] == 0) {
        floors.emplace_back(position);
        if (randomValue <= 0.1f)
          enemyManagerPtr->SpawnEnemy(position);
      } else if (roomMatrix[i][j] == 1) {
        walls.emplace_back(position);
        if (randomValue <= 0.1f)
          enemyManagerPtr->SpawnEnemy(
              Vector3Add(position, (Vector3){0.0f, WALL_HEIGHT, 0.0f}));
      } else if (roomMatrix[i][j] == 2) {
        columns.emplace_back(position);
      } else if (roomMatrix[i][j] == 3) {
        stairs.emplace_back(position);
      }
    }
  }
}

void BridgesRoom::Update() {
  Reset(playerPtr, enemyManagerPtr);

  // Collision checks
  CheckCollisionObjects(playerPtr, enemyManagerPtr, floors);
  CheckCollisionObjects(playerPtr, enemyManagerPtr, walls);
  CheckCollisionObjects(playerPtr, enemyManagerPtr, columns);
  CheckStairsCollision(playerPtr, enemyManagerPtr, stairs);

  // Enemy vision checks
  CheckEnemyVision(playerPtr, enemyManagerPtr, walls);
  CheckEnemyVision(playerPtr, enemyManagerPtr, columns);
  CheckEnemyVisionStairs(playerPtr, enemyManagerPtr, stairs);
}

void BridgesRoom::Draw() {
  BeginMode3D(playerPtr->camera);
  for (Plane &floor : floors) {
    floor.Draw();
  }
  for (Cube &wall : walls) {
    // wall.Draw();
    wall.DrawCubeTexture();
  }
  for (LargeColumn &column : columns) {
    column.Draw();
  }
  for (Stairs &stair : stairs) {
    stair.Draw();
  }
  EndMode3D();
}

// Returns reference to roomMatrix
const int (&BridgesRoom::GetRoomMatrix())[ROOM_SIZE][ROOM_SIZE] {
  return roomMatrix;
}
} // namespace World

// Helper Functions -------------------------------------------------------
//
// resets necessary player and enemy variables
void Reset(Entities::Player *player, Utility::EnemyManager *enemyManager) {
  // Reset
  player->SetPlaneCollision(false);
  // enemy->SetPlaneCollision(false);
  for (auto &enemy : *enemyManager->GetEnemiesVector()) {
    enemy->SetPlaneCollision(false);
  }
}

template <typename Object>
void CheckCollisionObjects(Entities::Player *player,
                           Utility::EnemyManager *enemyManager,
                           std::vector<Object> objects) {
  for (Object &obj : objects) {
    if (Utility::EntityCollisionObject(player, &obj)) {
      Utility::LockEntityAxis(player, &obj);
    }
    for (auto &enemy : *enemyManager->GetEnemiesVector()) {
      if (Utility::EntityCollisionObject(enemy.get(), &obj)) {
        Utility::LockEntityAxis(enemy.get(), &obj);
      }
    }
  }
}

void CheckStairsCollision(Entities::Player *player,
                          Utility::EnemyManager *enemyManager,
                          std::vector<World::Stairs> stairs) {
  // Checks collision between stairs and entities
  for (World::Stairs &stair : stairs) {
    World::Cube stairWall = stair.GetStairWall();
    if (Utility::EntityCollisionObject(player, &stairWall)) {
      Utility::LockEntityAxis(player, &stairWall);
    }
    for (auto &enemy : *enemyManager->GetEnemiesVector()) {
      if (Utility::EntityCollisionObject(enemy.get(), &stairWall)) {
        Utility::LockEntityAxis(enemy.get(), &stairWall);
      }
    }

    std::vector<World::Cube> stairCubes = stair.GetCubeVector();
    for (World::Cube &stairCube : stairCubes) {
      if (Utility::EntityCollisionObject(player, &stairCube)) {
        Utility::LockEntityAxis(player, &stairCube);
      }
      for (auto &enemy : *enemyManager->GetEnemiesVector()) {
        if (Utility::EntityCollisionObject(enemy.get(), &stairCube)) {
          Utility::LockEntityAxis(enemy.get(), &stairCube);
        }
      }
    }
  }
}

// checks if enemy vision is blocked by an object
template <typename Object>
void CheckEnemyVision(Entities::Player *player,
                      Utility::EnemyManager *enemyManager,
                      std::vector<Object> &objects) {
  for (Object &obj : objects) {
    // finding one wall where the vision ray collides
    for (auto &enemy : *enemyManager->GetEnemiesVector()) {
      if (!Utility::CanSeeTarget(enemy.get(), enemy->GetViewDistance(), player,
                                 &obj)) {
        if (enemy->GetState() != Entities::ENEMY_IDLE &&
            enemy->GetState() != Entities::ENEMY_DEAD) {
          enemy->SetIdle();
          break;
        }
      }
    }
  }
}

void CheckEnemyVisionStairs(Entities::Player *player,
                            Utility::EnemyManager *enemyManager,
                            std::vector<World::Stairs> &stairs) {
  for (World::Stairs &stair : stairs) {
    World::Cube stairWall = stair.GetStairWall();
    for (auto &enemy : *enemyManager->GetEnemiesVector()) {
      if (!Utility::CanSeeTarget(enemy.get(), enemy->GetViewDistance(), player,
                                 &stairWall) &&
          enemy->GetState() != Entities::ENEMY_IDLE &&
          enemy->GetState() != Entities::ENEMY_DEAD) {
        enemy->SetIdle();
        break;
      }
    }
  }
}
// End Helper Functions --------------------------------------------------------
//
