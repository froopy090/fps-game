#include "World/Test002.h"
#include "World/WorldDefinitions.h"
#include "Utility/Collision.h"
#include "raymath.h"

namespace World {
Test002::Test002() {
  // Cube init
  cube.size = (Vector3){2.0f, 1.0f, 2.0f};
  cube.position = (Vector3){10.0f, cube.size.y / 2.0f, 5.0f};
  cube.color = LIGHTGRAY;
  cube.boundingBox = Utility::InitCubeBoundingBox(cube);

  // Plane init
  floor.position = Vector3Zero();
  floor.dimension = (Vector2){32.0f, 32.0f};
  floor.color = DARKGRAY;
  floor.boundingBox = Utility::InitPlaneBoundingBox(floor);

  // Walls init
  leftWall.position = (Vector3){16.0f, 2.5f, 0.0f};
  leftWall.size = (Vector3){1.0f, 5.0f, 32.0f};
  leftWall.color = LIME;
  leftWall.boundingBox = Utility::InitCubeBoundingBox(leftWall);

  backWall.position = (Vector3){0.0f, 2.5f, 16.0f};
  backWall.size = (Vector3){32.0f, 5.0f, 1.0f};
  backWall.color = GOLD;
  backWall.boundingBox = Utility::InitCubeBoundingBox(backWall);

  rightWall.position = (Vector3){-16.0f, 2.5f, 0.0f};
  rightWall.size = (Vector3){1.0f, 5.0f, 32.0f};
  rightWall.color = BLUE;
  rightWall.boundingBox = Utility::InitCubeBoundingBox(rightWall);
}

void Test002::Update(Entities::Player *player, Entities::Enemy *enemy) {
  // Checks collision between player hitscan ray and columns
  if (Utility::HitscanIntersectsBox(player, cube.boundingBox)) {
    cube.color = RAYWHITE;
  } else {
    cube.color = LIGHTGRAY;
  }

  // Checks collision between player bounding box and columns
  if (CheckCollisionBoxes(player->GetBoundingBox(), cube.boundingBox)) {
    player->camera.position = player->GetPreviousPosition();
  }

  // Checks collision between enemy raycasts and columns
  // move left if right ray is close to column
  if (!enemy->IsDead() &&
      Vector3Distance(cube.position, enemy->GetPosition()) <=
          enemy->GetFeelers().viewDistance &&
      GetRayCollisionBox(enemy->GetFeelers().right, cube.boundingBox).hit) {
    enemy->MoveLeft();
  }
  // move right if left ray is close to column
  if (!enemy->IsDead() &&
      Vector3Distance(cube.position, enemy->GetPosition()) <=
          enemy->GetFeelers().viewDistance &&
      GetRayCollisionBox(enemy->GetFeelers().left, cube.boundingBox).hit) {
    enemy->MoveRight();
  }
  // slow down if center ray is close to column
  if (!enemy->IsDead() &&
      Vector3Distance(cube.position, enemy->GetPosition()) <=
          enemy->GetFeelers().viewDistance &&
      GetRayCollisionBox(enemy->GetFeelers().center, cube.boundingBox).hit) {
    enemy->SlowDown();
  }

  // Checks collision between enemy bounding box and columns
  if (!enemy->IsDead() &&
      CheckCollisionBoxes(enemy->GetBoundingBox(), cube.boundingBox)) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }

  // Checks collision between player and world map
  if (CheckCollisionBoxes(player->GetBoundingBox(), leftWall.boundingBox)) {
    player->camera.position = player->GetPreviousPosition();
  }
  if (CheckCollisionBoxes(player->GetBoundingBox(), backWall.boundingBox)) {
    player->camera.position = player->GetPreviousPosition();
  }
  if (CheckCollisionBoxes(player->GetBoundingBox(), rightWall.boundingBox)) {
    player->camera.position = player->GetPreviousPosition();
  }

  // Checks collision between enemy and world map
  if (enemy->IsDead() &&
      CheckCollisionBoxes(enemy->GetBoundingBox(), leftWall.boundingBox)) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }
  if (CheckCollisionBoxes(enemy->GetBoundingBox(), backWall.boundingBox)) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }
  if (CheckCollisionBoxes(enemy->GetBoundingBox(), rightWall.boundingBox)) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }
}

void Test002::Draw(Entities::Player *player) {
  // TODO: draw map here
  BeginMode3D(player->camera);

  DrawPlane(floor.position, floor.dimension, floor.color);

  DrawCubeV(cube.position, cube.size, cube.color);
  DrawBoundingBox(cube.boundingBox, BLACK);

  DrawCubeV(leftWall.position, leftWall.size, leftWall.color);
  DrawBoundingBox(leftWall.boundingBox, BLACK);

  DrawCubeV(backWall.position, backWall.size, backWall.color);
  DrawBoundingBox(backWall.boundingBox, BLACK);

  DrawCubeV(rightWall.position, rightWall.size, rightWall.color);
  DrawBoundingBox(rightWall.boundingBox, BLACK);

  DrawGrid(10, 1.0f);
  EndMode3D();
}

BoundingBox Test002::GetPlaneBoundingBox() { return floor.boundingBox; }
} // namespace World
