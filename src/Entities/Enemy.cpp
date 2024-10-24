#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "raylib.h"
#include "raymath.h"

namespace Entities {
Enemy::Enemy() {
  // Dimensions init
  size.width = 0.5f;
  size.height = 1.5f;
  size.length = 0.5f;

  // Sprite init
  sprite.texture = LoadTexture("DOOM_Enemy.png");
  sprite.source = (Rectangle){3, 1, 77, 90};
  sprite.tint = WHITE;

  // Position init
  position = (Vector3){0.0f, 0.0f, -4.0f};

  // Bounding box init
  boundingBox.min = (Vector3){position.x - size.width / 2.0f, 0.0f,
                              position.z - size.length / 2.0f};
  boundingBox.max = (Vector3){position.x + size.width / 2.0f, size.height,
                              position.z + size.length / 2.0f};

  // Health init
  health = 100.0f;
}

Enemy::~Enemy() { UnloadTexture(sprite.texture); }

void Enemy::Event() {
  // TODO: add event function
}

void Enemy::Update(Player *player) {
  // Checks collision between player hitscan ray and Enemy bounding box
  if (Utility::HitscanIntersectsBox(player, boundingBox)) {
    // Takes damage
    health -= 30;
  }

  // Checking health
  if (health <= 0.0f) {
    sprite.tint = BLANK;
  }
}

void Enemy::Draw(Player *player) {
  BeginMode3D(player->camera);
  DrawBoundingBox(boundingBox, BLACK);
  DrawBillboardRec(
      player->camera, sprite.texture, sprite.source,
      Vector3Add(position, (Vector3){0.0f, size.height / 2.0f, 0.0f}),
      (Vector2){size.width * 2.0f, size.height}, sprite.tint);
  EndMode3D();
}
} // namespace Entities
