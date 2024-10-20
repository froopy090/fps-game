#pragma once
#include "Utility/Timer.h"
#include "raylib.h"

namespace Entities {
struct Size{
  float width;
  float height;
  float length;
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
  BoundingBox GetBoundingBox();
  void SavePosition();
  Vector3 GetPreviousPosition();

private:
  Size size;
  float health;
  Utility::Timer timer;
  BoundingBox boundingBox;
  Vector3 previousPosition;
};
} // namespace Entities
