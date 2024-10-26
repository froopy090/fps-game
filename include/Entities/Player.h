#pragma once
#include "Entities/EntityDefinitions.h"
#include "Utility/Timer.h"
#include "raylib.h"

namespace World {
class TestMap;
class Test002;
}

namespace Entities {
class Player {
public:
  Camera3D camera;
  int cameraMode;

  Player();
  void Event();
  void Update(World::TestMap *testMap);
  void Update(World::Test002 *testMap);
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
