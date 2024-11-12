#pragma once
#include "Entities/EntityDefinitions.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
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
  bool IsDead();
  Feelers GetFeelers();

  // Setters
  void SetPosition(Vector3 position);
  void SetXPosition(float x);
  void SetYPosition(float y);
  void SetZPosition(float z);
  void SetPlaneCollision(bool b);

  //  Helper functions
  void SavePosition();
  void MoveRight();
  void MoveLeft();
  void SlowDown();
  void ResetSpeed();

private:
  // Enemy Info
  Vector3 size;
  Vector3 position;
  Vector3 upAxis;
  float health;
  bool dead;
  float meleeDamage;
  EnemySprite sprite;

  // Collision
  BoundingBox boundingBox;
  Vector3 previousPosition;
  Feelers feelers;
  bool planeCollision;

  // Movement
  Vector3 forward;
  Vector3 velocity;
  float speed;
  float gravity;

  // Utility
  Utility::Timer timer;
};
} // namespace Entities
