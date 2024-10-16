#include "World/TestMap.h"
#include "Entities/Player.h"
#include "raylib.h"

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
}

void TestMap::Update(Entities::Player *player) {
  for (int i = 0; i < MAX_COLUMNS; i++) {
    if (player->isShooting && GetRayCollisionBox(player->GetRay(), boundingBox[i]).hit) {
      colors[i] = BLANK;
    } else {
      colors[i] = tempColors[i];
    }
  }
}

void TestMap::Draw(Entities::Player *player) {
  // TODO add draw calls in here
  BeginMode3D(player->camera);

  DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
            LIGHTGRAY); // draw ground
  DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
           BLUE); // draw blue wall
  DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
           LIME); // draw green wall
  DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
           GOLD); // draw yellow wall
  DrawGrid(10, 1.0f);

  // Draw some cubes around
  for (int i = 0; i < MAX_COLUMNS; i++) {
    DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
    DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
    DrawBoundingBox(boundingBox[i], BLACK);
  }

  EndMode3D();
}
} // namespace World
