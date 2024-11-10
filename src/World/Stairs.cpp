#include "World/Stairs.h"
#include "World/WorldDefinitions.h"
#include "raylib.h"
#include "raymath.h"

namespace World {
Stairs::Stairs(Vector3 position) : stairWall(position) {
  stairCount = 5;
  stairSize = (Vector3){TILE_SIZE, WALL_HEIGHT / (float)stairCount, TILE_SIZE};

  stairWall.SetPosition(Vector3Add(
      position, (Vector3){0.0f, WALL_HEIGHT / 2.0f, stairWall.GetSize().z}));

  for (int i = 0; i < stairCount; i++) {
    stairs.emplace_back(position, stairSize);
    position = Vector3Add(
        position, (Vector3){0.0f, (WALL_HEIGHT / (float)stairCount), 1.0f});
  }

  /*float newWidth = stairWall.GetSize().z / 2.0f + 1.0f;*/
  /*stairWall.SetSize((Vector3){stairWall.GetSize().x, WALL_HEIGHT,
   * newWidth});*/
  /*stairWall.SetPosition(*/
  /*    (Vector3){position.x, position.y / 2.0f, position.z - newWidth
   * / 2.0f});*/
}

void Stairs::Draw() {
  for (Cube &stair : stairs) {
    stair.Draw();
  }
  stairWall.Draw();
}

// Getters
int Stairs::GetStairCount() { return stairCount; }
Vector3 Stairs::GetStairSize() { return stairSize; }
Cube Stairs::GetStairWall() { return stairWall; }
std::vector<Cube> Stairs::GetCubeVector() { return stairs; }

// Setters
void Stairs::SetStairCount(int stairCount) { this->stairCount = stairCount; }
void Stairs::SetStairSize(Vector3 stairSize) { this->stairSize = stairSize; }
} // namespace World
