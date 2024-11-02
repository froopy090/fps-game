#pragma once
#include "Entities/EntityDefinitions.h"
#include "Utility/Timer.h"
#include "raylib.h"

namespace Entities {
class Player {
public:
  Camera3D camera;
  int cameraMode;

  // Main methods
  Player();
  void Event();
  void Update();
  void Draw();

  // Getters
  // returns center of bounding box, NOT camera position
  Vector3 GetPosition();
  Vector3 GetSize();
  // returns hitscan ray
  Ray GetRay();
  BoundingBox GetBoundingBox();
  Vector3 GetPreviousPosition();
  bool IsShooting();
  float GetHealth();
  bool GetStairFlag();

  // Setters
  // sets previousPosition to the current camera position
  void SavePosition();
  void TakeDamage(float damage);
  void SetPlaneCollision(bool b);
  void SetStairFlag(bool b);
  void Gravity(bool b);

private:
  // Player info
  Vector3 size;
  float health;

  // Firing weapon
  bool isShooting;
  Utility::Timer timer;

  // Collisions
  BoundingBox boundingBox;
  Vector3 previousPosition;

  // Jumping/gravity
  bool gravityOn;
  float gravity;
  float jumpVelocity;
  bool isJumping;
  bool planeCollision;

  //Stairs
  bool isOnStair;
};
} // namespace Entities
