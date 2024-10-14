#pragma once
#include "raylib.h"

namespace Entities {
struct PlayerCube {
  Vector3 position;
  float width;
  float height;
  float length;
  Color color;
};

class Player {
public:
  Camera3D camera;
  int cameraMode;
  Player();
  void Event();
  void Update();
  void Draw();

private:
  PlayerCube playerCube;
  float health;
};
} // namespace Entities
