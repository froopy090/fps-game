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
  Vector3 GetVelocity();

  // Setters
  // sets previousPosition to the current camera position
  void SavePosition();
  void SetXPosition(float x);
  void SetYPosition(float y);
  void SetZPosition(float z);
  void TakeDamage(float damage);
  void SetPlaneCollision(bool b);
  void SetStairFlag(bool b);
  void Gravity(bool b);
  void SetVelocity(Vector3 velocity);

private:
  // Player info
  Vector3 size;
  Vector3 velocity;
  float health;
  float speed;
  float mouseSensitivity;

  // Firing weapon
  bool isShooting;
  Utility::Timer timer;

  // Collisions
  BoundingBox boundingBox;
  Vector3 previousPosition;

  // Jumping/gravity
  float gravity;
  float jumpVelocity;
  bool isJumping;
  bool planeCollision;

  // Stairs
  bool isOnStair;
};
} // namespace Entities
