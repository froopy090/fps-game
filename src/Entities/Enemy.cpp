#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "raylib.h"
#include "raymath.h"

namespace Entities {
Enemy::Enemy(Player *player) {
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
  previousPosition = position;

  // Bounding box init
  boundingBox.min = (Vector3){position.x - size.width / 2.0f, 0.0f,
                              position.z - size.length / 2.0f};
  boundingBox.max = (Vector3){position.x + size.width / 2.0f, size.height,
                              position.z + size.length / 2.0f};

  // Health init
  health = 150.0f;

  // Forward-facing direction init (unit vector)
  forward = Vector3Zero();
  // Speed init
  speed = 1.0f;
}

Enemy::~Enemy() { UnloadTexture(sprite.texture); }

void Enemy::Event() {
  // TODO: add event function
}

void Enemy::Update(Player *player, Pistol *pistol) {
  // Save position before updating
  this->SavePosition();

  // Checks collision between player hitscan ray and Enemy bounding box
  if (Utility::HitscanIntersectsBox(player, boundingBox)) {
    // Takes damage
    health -= pistol->GetDamage();
  }

  // Checking health
  if (health <= 0.0f) {
    sprite.tint = BLANK;
  }

  // Move towards player
  forward = Vector3Normalize(Vector3Subtract(player->GetPosition(), position));
  position =
      Vector3Add(position, Vector3Scale(forward, speed * GetFrameTime()));

  // Updating bounding box position
  boundingBox.min = (Vector3){position.x - size.width / 2.0f, position.y,
                              position.z - size.length / 2.0f};
  boundingBox.max =
      (Vector3){position.x + size.width / 2.0f, position.y + size.height,
                position.z + size.length / 2.0f};
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

void Enemy::SavePosition() { previousPosition = position; }

Vector3 Enemy::GetPreviousPosition() { return previousPosition; }

BoundingBox Enemy::GetBoundingBox() { return boundingBox; }

Vector3 Enemy::GetPosition() { return position; }

void Enemy::SetPosition(Vector3 position) { this->position = position; }
} // namespace Entities
