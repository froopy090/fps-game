#include "World/TestMap.h"
#include "Entities/Player.h"
#include "raylib.h"
#include "raymath.h"

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
  plane.boundingBox.min =
      (Vector3){-plane.dimension.x / 2.0f, 0.0f, -plane.dimension.y / 2.0f};
  plane.boundingBox.max =
      (Vector3){plane.dimension.x / 2.0f, 0.0f, plane.dimension.y / 2.0f};

  leftWall.position = (Vector3){16.0f, 2.5f, 0.0f};
  leftWall.size = (Vector3){1.0f, 5.0f, 32.0f};
  leftWall.color = LIME;
  leftWall.boundingBox.min =
      (Vector3){leftWall.position.x - leftWall.size.x / 2.0f, 0.0f,
                leftWall.position.z - leftWall.size.z / 2.0f};
  leftWall.boundingBox.max =
      (Vector3){leftWall.position.x + leftWall.size.x / 2.0f, leftWall.size.y,
                leftWall.position.z + leftWall.size.z / 2.0f};

  backWall.position = (Vector3){0.0f, 2.5f, 16.0f};
  backWall.size = (Vector3){32.0f, 5.0f, 1.0f};
  backWall.color = GOLD;
  backWall.boundingBox.min =
      (Vector3){backWall.position.x - backWall.size.x / 2.0f, 0.0f,
                backWall.position.z - backWall.size.z / 2.0f};
  backWall.boundingBox.max =
      (Vector3){backWall.position.x + backWall.size.x / 2.0f, backWall.size.y,
                backWall.position.z + backWall.size.z / 2.0f};

  rightWall.position = (Vector3){-16.0f, 2.5f, 0.0f};
  rightWall.size = (Vector3){1.0f, 5.0f, 32.0f};
  rightWall.color = BLUE;
  rightWall.boundingBox.min =
      (Vector3){rightWall.position.x - rightWall.size.x / 2.0f, 0.0f,
                rightWall.position.z - rightWall.size.z / 2.0f};
  rightWall.boundingBox.max = (Vector3){
      rightWall.position.x + rightWall.size.x / 2.0f, rightWall.size.y,
      rightWall.position.z + rightWall.size.z / 2.0f};
}

void TestMap::Update(Entities::Player *player) {
  // Checks collision between player hitscan ray and columns
  for (int i = 0; i < MAX_COLUMNS; i++) {
    if (player->isShooting &&
        GetRayCollisionBox(player->GetRay(), boundingBox[i]).hit) {
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
}

void TestMap::Draw(Entities::Player *player) {
  // TODO add draw calls in here
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
