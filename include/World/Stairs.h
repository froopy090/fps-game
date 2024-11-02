#pragma once
#include "World/BaseObjects.h"
#include "raylib.h"
#include <vector>

namespace World {
class Stairs {
public:
  // Main methods
  Stairs(Vector3 position);
  void Draw();

  // Getters
  int GetStairCount();
  Vector3 GetStairSize();
  std::vector<Cube> GetCubeVector();

  // Setters
  void SetStairCount(int stairCount);
  void SetStairSize(Vector3 size);

private:
  int stairCount;
  Vector3 stairSize;
  std::vector<Cube> stairs;
};
} // namespace World
