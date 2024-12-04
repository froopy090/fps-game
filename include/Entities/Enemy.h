#pragma once
#include "Entities/EntityDefinitions.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "GameObject.h"
#include "Utility/Timer.h"
#include "memory"
#include "raylib.h"

namespace Entities {
class Enemy : public GameObject {
public:
  // Main methods
  Enemy(Player *player, Pistol *pistol, Vector3 position);
  ~Enemy();
  void Event() override;
  void Update() override;
  void Draw() override;

  // Getters
  Vector3 GetPosition();
  Vector3 GetPreviousPosition();
  Vector3 GetSize();
  Vector3 GetVelocity();
  BoundingBox GetBoundingBox();
  Ray GetRay();
  EnemyState GetState();
  float GetViewDistance();

  // Setters
  void SetPosition(Vector3 position);
  void SetXPosition(float x);
  void SetYPosition(float y);
  void SetZPosition(float z);
  void SetPlaneCollision(bool b);
  void SetChasePlayer();
  void SetIdle();

  //  Helper functions
  void SavePosition();
  static void CleanupSprite() {
    if (sprite)
      sprite.reset();
  };

private:
  // Enemy Info
  const static Vector3 size;
  Vector3 position;
  const static Vector3 upAxis;
  float health;
  EnemyState state;
  const static float meleeDamage;
  static std::unique_ptr<EnemySprite> sprite;

  // Other stuff
  Player *player;
  Pistol *pistol;

  // Collision
  BoundingBox boundingBox;
  Vector3 previousPosition;
  Ray visionRay;
  bool planeCollision;

  // Movement
  Vector3 forward;
  Vector3 velocity;
  const static float speed;
  const static float gravity;
  float randomAngle;
  const static float viewDistance;

  // Utility
  Utility::Timer movementTimer;
  Utility::Timer searchTimer;
};
} // namespace Entities
