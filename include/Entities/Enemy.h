#pragma once
#include "Entities/EntityDefinitions.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "raylib.h"

namespace Entities {
class Enemy {
  public:
  Enemy(Player *player);
  ~Enemy();
  void Event();
  void Update(Player *player, Pistol *pistol);
  void Draw(Player *player);
  void SavePosition();
  Vector3 GetPosition();
  Vector3 GetPreviousPosition();
  BoundingBox GetBoundingBox();
  void SetPosition(Vector3 position);
  bool IsDead();
  Feelers GetFeelers();
  void MoveRight();
  void MoveLeft();
  void SlowDown();
  void ResetSpeed();

private:
  Size size;
  Vector3 position;
  Vector3 upAxis;
  EnemySprite sprite;
  float health;
  float meleeDamage;
  bool dead;
  BoundingBox boundingBox;
  Vector3 forward;
  float speed;
  Vector3 previousPosition;
  Feelers feelers;
  Utility::Timer timer;
};
} // namespace Entities
