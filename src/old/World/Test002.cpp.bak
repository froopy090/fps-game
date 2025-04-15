#include "World/Test002.h"
#include "Utility/Collision.h"
#include "World/WorldDefinitions.h"
#include "World/BaseObjects.h"
#include "raylib.h"
#include "raymath.h"

namespace World {
Test002::Test002()
    : floor(Vector3Zero()), leftWall((Vector3){TILE_SIZE, 0.0f, 0.0f}),
      backWall((Vector3){0.0f, 0.0f, TILE_SIZE}),
      rightWall((Vector3){-TILE_SIZE, 0.0f, 0.0f}),
      cube((Vector3){TILE_SIZE, 0.0f, -TILE_SIZE}) {}

void Test002::Update(Entities::Player *player, Entities::Enemy *enemy) {
  // Checks collision between player hitscan ray and columns
  if (Utility::HitscanIntersectsBox(player, &cube)) {
    cube.SetColor(RAYWHITE);
  } else {
    cube.SetColor(LIGHTGRAY);
  }

  // Checks collision between player and plane
  player->SetPlaneCollision(Utility::EntityCollisionObject(player, &floor));

  // Checks collision between player bounding box and columns
  if (CheckCollisionBoxes(player->GetBoundingBox(), cube.GetBoundingBox())) {
    player->camera.position = player->GetPreviousPosition();
  }

  // Checks collision between enemy raycasts and columns
  // move left if right ray is close to column
  if (!enemy->IsDead() &&
      Vector3Distance(cube.GetPosition(), enemy->GetPosition()) <=
          enemy->GetFeelers().viewDistance &&
      GetRayCollisionBox(enemy->GetFeelers().right, cube.GetBoundingBox())
          .hit) {
    enemy->MoveLeft();
  }
  // move right if left ray is close to column
  if (!enemy->IsDead() &&
      Vector3Distance(cube.GetPosition(), enemy->GetPosition()) <=
          enemy->GetFeelers().viewDistance &&
      GetRayCollisionBox(enemy->GetFeelers().left, cube.GetBoundingBox()).hit) {
    enemy->MoveRight();
  }
  // slow down if center ray is close to column
  if (!enemy->IsDead() &&
      Vector3Distance(cube.GetPosition(), enemy->GetPosition()) <=
          enemy->GetFeelers().viewDistance &&
      GetRayCollisionBox(enemy->GetFeelers().center, cube.GetBoundingBox())
          .hit) {
    enemy->SlowDown();
  }

  // Checks collision between enemy bounding box and columns
  if (!enemy->IsDead() &&
      CheckCollisionBoxes(enemy->GetBoundingBox(), cube.GetBoundingBox())) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }

  // Checks collision between player and world map
  if (CheckCollisionBoxes(player->GetBoundingBox(),
                          leftWall.GetBoundingBox())) {
    player->camera.position = player->GetPreviousPosition();
  }
  if (CheckCollisionBoxes(player->GetBoundingBox(),
                          backWall.GetBoundingBox())) {
    player->camera.position = player->GetPreviousPosition();
  }
  if (CheckCollisionBoxes(player->GetBoundingBox(),
                          rightWall.GetBoundingBox())) {
    player->camera.position = player->GetPreviousPosition();
  }

  // Checks collision between enemy and world map
  if (enemy->IsDead() &&
      CheckCollisionBoxes(enemy->GetBoundingBox(), leftWall.GetBoundingBox())) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }
  if (CheckCollisionBoxes(enemy->GetBoundingBox(), backWall.GetBoundingBox())) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }
  if (CheckCollisionBoxes(enemy->GetBoundingBox(),
                          rightWall.GetBoundingBox())) {
    enemy->SetPosition(enemy->GetPreviousPosition());
  }
}

void Test002::Draw(Entities::Player *player) {
  BeginMode3D(player->camera);

  floor.Draw();
  leftWall.Draw();
  backWall.Draw();
  rightWall.Draw();
  cube.Draw();

  DrawGrid(10, 1.0f);
  EndMode3D();
}

BoundingBox Test002::GetPlaneBoundingBox() { return floor.GetBoundingBox(); }

bool Test002::CheckPlaneCollisionPlayer(BoundingBox playerBox) {
  return CheckCollisionBoxes(playerBox, floor.GetBoundingBox());
}
} // namespace World
