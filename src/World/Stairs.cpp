#include "World/Stairs.h"
#include "World/WorldDefinitions.h"
#include "raylib.h"
#include "raymath.h"

namespace World {
Stairs::Stairs(Vector3 position) {
  stairCount = 5;
  stairSize = (Vector3){TILE_SIZE, WALL_HEIGHT / (float)stairCount, TILE_SIZE};

  for (int i = 0; i < stairCount; i++) {
    stairs.emplace_back(position, stairSize);
    position = Vector3Add(
        position, (Vector3){0.0f, (WALL_HEIGHT / (float)stairCount), 1.0f});
  }
}

void Stairs::Draw() {
  for (Cube &stair : stairs) {
    stair.Draw();
  }
}

// Getters
int Stairs::GetStairCount() { return stairCount; }
Vector3 Stairs::GetStairSize() { return stairSize; }
std::vector<Cube> Stairs::GetCubeVector() { return stairs; }

// Setters
void Stairs::SetStairCount(int stairCount) { this->stairCount = stairCount; }
void Stairs::SetStairSize(Vector3 stairSize) { this->stairSize = stairSize; }
} // namespace World
