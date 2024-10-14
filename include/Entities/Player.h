#pragma once
#include "raylib.h"

namespace Entities {
struct PlayerCube{
    Vector3 position;
    float width;
    float height;
    float length;
    Color color;
};

class Player {
public:
  void Event();
  void Update();
  void Draw();

private:
  Vector3 position;
  PlayerCube playerCube;
  Camera3D camera;
  float health;
};
} // namespace Entities
