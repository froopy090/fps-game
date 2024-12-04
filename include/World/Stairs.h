#pragma once
#include "GameObject.h"
#include "World/BaseObjects.h"
#include "raylib.h"
#include <vector>

namespace World {
class Stairs : public GameObject {
public:
  // Main methods
  Stairs(Vector3 position);
  void Event() override;
  void Update() override;
  void Draw() override;

  // Getters
  int GetStairCount();
  Vector3 GetStairSize();
  Cube GetStairWall();
  std::vector<Cube> GetCubeVector();

  // Setters
  void SetStairCount(int stairCount);
  void SetStairSize(Vector3 size);

private:
  int stairCount;
  Vector3 stairSize;
  Cube stairWall;
  std::vector<Cube> stairs;
};
} // namespace World
