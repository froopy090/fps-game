#pragma once
#include "Utility/Timer.h"
#include "raylib.h"

namespace Entities {
struct Size{
  //Vector3 position;
  float width;
  float height;
  float length;
  //Color color;
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
  //PlayerCube playerCube;
  Size size;
  float health;
  Utility::Timer timer;
  BoundingBox boundingBox;
  Vector3 previousPosition;
};
} // namespace Entities
