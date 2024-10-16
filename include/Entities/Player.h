#pragma once
#include "raylib.h"
#include "Utility/Timer.h"

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
  bool isShooting;

  Player();
  void Event();
  void Update();
  void Draw();
  Vector3 GetPosition();
  Ray GetRay();

private:
  PlayerCube playerCube;
  float health;
  Utility::Timer timer;
};
} // namespace Entities
