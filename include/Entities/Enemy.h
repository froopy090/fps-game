#pragma once
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "raylib.h"

namespace Entities {
class Enemy {
  struct EnemySprite {
    Texture2D texture;
    Rectangle source;
    Color tint;
  };

public:
  Enemy();
  ~Enemy();
  void Event();
  void Update(Player *player, Pistol *pistol);
  void Draw(Player *player);

private:
  Size size;
  Vector3 position;
  EnemySprite sprite;
  float health;
  BoundingBox boundingBox;
};
} // namespace Entities
