#pragma once
#include "raylib.h"

namespace Entities {
struct EnemySprite {
  Texture2D texture;
  Rectangle source;
  Color tint;

  ~EnemySprite() { UnloadTexture(texture); }
};

struct Sprite {
  Rectangle source;
  Rectangle destination;
  Vector2 origin;
  float rotation;
  Color tint;
};

struct Size {
  float width;
  float height;
  float length;
};

typedef enum WeaponState {
  WEAPON_IDLE,
  WEAPON_FIRING,
  WEAPON_RELOADING
} WeaponState;

typedef enum EnemyState {
  ENEMY_IDLE = 0,
  ENEMY_CHASING,
  ENEMY_ATTACKING,
  ENEMY_DEAD
} EnemyState;

} // namespace Entities
