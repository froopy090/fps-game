#include "World/TestMap.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "raylib.h"
#include "raymath.h"
#include <iterator>

namespace World {
TestMap::TestMap() {
  // Generate random columns
  for (int i = 0; i < MAX_COLUMNS; i++) {
    heights[i] = (float)GetRandomValue(1, 12);
    positions[i] = (Vector3){(float)GetRandomValue(-15, 15), heights[i] / 2.0f,
                             (float)GetRandomValue(-15, 15)};
    colors[i] = (Color){GetRandomValue(20, 255), GetRandomValue(10, 55), 30,
                        255}; // this isn't actually an error
    tempColors[i] = colors[i];
    boundingBox[i].min =
        (Vector3){positions[i].x - 1.0f, 0.0f, positions[i].z - 1.0f};
    boundingBox[i].max =
        (Vector3){positions[i].x + 1.0f, heights[i], positions[i].z + 1.0f};
  }

  // Generate map
  plane.position = Vector3Zero();
  plane.dimension = (Vector2){32.0f, 32.0f};
  plane.color = LIGHTGRAY;
  plane.boundingBox = InitPlaneBoundingBox(plane);

  leftWall.position = (Vector3){16.0f, 2.5f, 0.0f};
  leftWall.size = (Vector3){1.0f, 5.0f, 32.0f};
  leftWall.color = LIME;
  leftWall.boundingBox = InitCubeBoundingBox(leftWall);

  backWall.position = (Vector3){0.0f, 2.5f, 16.0f};
  backWall.size = (Vector3){32.0f, 5.0f, 1.0f};
  backWall.color = GOLD;
  backWall.boundingBox = InitCubeBoundingBox(backWall);

  rightWall.position = (Vector3){-16.0f, 2.5f, 0.0f};
  rightWall.size = (Vector3){1.0f, 5.0f, 32.0f};
  rightWall.color = BLUE;
  rightWall.boundingBox = InitCubeBoundingBox(rightWall);
}

void TestMap::Update(Entities::Player *player, Entities::Enemy *enemy) {
  // Checks collision between player hitscan ray and columns
  for (int i = 0; i < MAX_COLUMNS; i++) {
    if (Utility::HitscanIntersectsBox(player, boundingBox[i])) {
      colors[i] = BLANK;
    } else {
      colors[i] = tempColors[i];
    }
  }

  // Checks collision between player bounding box and columns
  for (int i = 0; i < MAX_COLUMNS; i++) {
    if (CheckCollisionBoxes(player->GetBoundingBox(), boundingBox[i])) {
      player->camera.position = player->GetPreviousPosition();
    }
  }

  // Checks collision between enemy bounding box and columns
  for (int i = 0; i < MAX_COLUMNS; i++) {
    if (!enemy->IsDead() &&
        CheckCollisionBoxes(enemy->GetBoundingBox(), boundingBox[i])) {
      enemy->SetPosition(enemy->GetPreviousPosition());
    }
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

void TestMap::Draw(Entities::Player *player) {
  BeginMode3D(player->camera);

  DrawPlane(plane.position, plane.dimension, plane.color);

  DrawCubeV(leftWall.position, leftWall.size, leftWall.color);
  DrawBoundingBox(leftWall.boundingBox, BLACK);

  DrawCubeV(backWall.position, backWall.size, backWall.color);
  DrawBoundingBox(backWall.boundingBox, BLACK);

  DrawCubeV(rightWall.position, rightWall.size, rightWall.color);
  DrawBoundingBox(rightWall.boundingBox, BLACK);

  DrawGrid(10, 1.0f);

  // Draw some cubes around
  for (int i = 0; i < MAX_COLUMNS; i++) {
    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
    DrawBoundingBox(boundingBox[i], BLACK);
  }

  EndMode3D();
}

BoundingBox TestMap::GetPlaneBoundingBox() { return plane.boundingBox; }
} // namespace World
