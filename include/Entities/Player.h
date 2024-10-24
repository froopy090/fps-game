#pragma once
#include "Utility/Timer.h"
#include "raylib.h"

namespace World {
class TestMap;
}

namespace Entities {
struct Size {
  float width;
  float height;
  float length;
};

class Player {
public:
  Camera3D camera;
  int cameraMode;

  Player();
  void Event();
  void Update(World::TestMap *testMap);
  void Draw();
  Vector3 GetPosition();
  Ray GetRay();
  BoundingBox GetBoundingBox();
  void SavePosition();
  Vector3 GetPreviousPosition();
  void TakeDamage(float damage);
  bool IsShooting();
  float GetHealth();

private:
  Size size;
  float health;
  bool isShooting;
  Utility::Timer timer;
  BoundingBox boundingBox;
  Vector3 previousPosition;
  float gravity;
  float jumpVelocity;
  bool isJumping;
};
} // namespace Entities
