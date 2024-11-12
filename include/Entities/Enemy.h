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
  BoundingBox GetBoundingBox();
  bool IsDead();
  Feelers GetFeelers();

  // Setters
  void SetPosition(Vector3 position);

  //  Helper functions
  void SavePosition();
  void MoveRight();
  void MoveLeft();
  void SlowDown();
  void ResetSpeed();

private:
  // Enemy Info
  Size size;
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

  // Movement
  Vector3 forward;
  float speed;

  // Utility
  Utility::Timer timer;
};
} // namespace Entities
