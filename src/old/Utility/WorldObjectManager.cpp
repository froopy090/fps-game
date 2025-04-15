#include "Utility/WorldObjectManager.h"
#include "Utility/Collision.h"
#include "raylib.h"
//don't remove raymath, for some reason it needs it
#include "raymath.h"

namespace Utility {
WorldObjectManager::WorldObjectManager(Entities::Player *player,
                                       EnemyManager *enemyManager)
    : player(player), enemyManager(enemyManager) {}

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

void WorldObjectManager::Update() {
  // Collision checks
  CheckCollisionObjects(player, enemyManager, planes);
  CheckCollisionObjects(player, enemyManager, cubes);
  CheckCollisionObjects(player, enemyManager, columns);
  CheckStairsCollision(player, enemyManager, stairs);

  // Enemy vision checks
  CheckEnemyVision(player, enemyManager, planes);
  CheckEnemyVision(player, enemyManager, cubes);
  CheckEnemyVision(player, enemyManager, columns);
  CheckEnemyVisionStairs(player, enemyManager, stairs);
}

void WorldObjectManager::Draw() {
  BeginMode3D(player->camera);
  for (World::Plane &plane : planes) {
    plane.DrawPlaneTexture();
  }
  for (World::Cube &cube : cubes) {
    cube.DrawCubeTexture();
  }
  for (World::LargeColumn &column : columns) {
    column.DrawCubeTexture();
  }
  for (World::Stairs &stair : stairs) {
    stair.Draw();
  }
  EndMode3D();
}

// Helper functions -----------------------------------------------
template <typename Object>
void WorldObjectManager::CheckCollisionObjects(
    Entities::Player *player, Utility::EnemyManager *enemyManager,
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

void WorldObjectManager::CheckStairsCollision(
    Entities::Player *player, Utility::EnemyManager *enemyManager,
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
void WorldObjectManager::CheckEnemyVision(Entities::Player *player,
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

void WorldObjectManager::CheckEnemyVisionStairs(
    Entities::Player *player, Utility::EnemyManager *enemyManager,
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
// End Helper Functions
// ----------------------------------------------------------
} // namespace Utility
