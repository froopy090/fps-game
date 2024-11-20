#pragma once
#include "Entities/EntityDefinitions.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/Timer.h"
#include "raylib.h"

namespace Entities {
class Enemy {
public:
  // Main methods
  Enemy(Player *player);
  ~Enemy();
  void Event();
  void Update(Player *player, Pistol *pistol);
  void Draw(Player *player);

  // Getters
  Vector3 GetPosition();
  Vector3 GetPreviousPosition();
  Vector3 GetSize();
  Vector3 GetVelocity();
  BoundingBox GetBoundingBox();
  Ray GetRay();
  bool RayHasCollided();
  EnemyState GetState();

  // Setters
  void SetPosition(Vector3 position);
  void SetXPosition(float x);
  void SetYPosition(float y);
  void SetZPosition(float z);
  void SetPlaneCollision(bool b);
  void SetChasePlayer();
  void SetIdle();
  //void SetState(EnemyState state);
  void SetRayHasCollided(bool b);

  //  Helper functions
  void SavePosition();
  void MoveRight();
  void MoveLeft();
  void ResetSpeed();

private:
  // Enemy Info
  Vector3 size;
  Vector3 position;
  Vector3 upAxis;
  float health;
  EnemyState state;
  float meleeDamage;
  EnemySprite sprite;

  // Collision
  BoundingBox boundingBox;
  Vector3 previousPosition;
  Ray visionRay;
  bool planeCollision;
  bool rayHasCollided;

  // Movement
  Vector3 forward;
  Vector3 velocity;
  float speed;
  float gravity;
  // bool chasePlayer;

  // Utility
  Utility::Timer movementTimer;
};
} // namespace Entities
