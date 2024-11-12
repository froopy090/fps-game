#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "iostream"
#include "raylib.h"
#include "raymath.h"
#include <cctype>

namespace Entities {
// Main Methods -----------------------------------------------------------
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
  upAxis = (Vector3){0.0f, 1.0f, 0.0f};

  // Bounding box init
  boundingBox.min = (Vector3){position.x - size.width / 2.0f, 0.0f,
                              position.z - size.length / 2.0f};
  boundingBox.max = (Vector3){position.x + size.width / 2.0f, size.height,
                              position.z + size.length / 2.0f};

  // Health init
  health = 150.0f;
  dead = false;

  // Damage init
  meleeDamage = 25.0f;

  // Forward-facing direction init (unit vector)
  forward = Vector3Zero();
  // Speed init
  speed = 2.0f;

  // Feelers init
  feelers.center = {Vector3Zero(), Vector3Zero()};
  feelers.centerEndPoint = Vector3Zero();
  feelers.right = {Vector3Zero(), Vector3Zero()};
  feelers.rightEndPoint = Vector3Zero();
  feelers.left = {Vector3Zero(), Vector3Zero()};
  feelers.leftEndPoint = Vector3Zero();
  feelers.viewDistance = 100.0f;
  feelers.angle = 0.10f;
}

Enemy::~Enemy() { UnloadTexture(sprite.texture); }

void Enemy::Event() {
  // TODO: add event function
  if (!dead) {
  }
}

void Enemy::Update(Player *player, Pistol *pistol) {
  if (!dead) {
    // Save position before updating
    this->SavePosition();

    // Update timer
    timer.Update();

    // Checks collision between player hitscan ray and Enemy bounding box
    if (Utility::HitscanIntersectsBox(player, this)) {
      // Takes damage
      health -= pistol->GetDamage();
    }

    // Checking health
    if (health <= 0.0f) {
      dead = true;
      sprite.tint = BLANK;
    }

    // Checking if needs to slow down
    if (!timer.Finished()) {
      speed = 1.0f;
    } else {
      this->ResetSpeed();
    }

    // Move towards player
    forward =
        Vector3Normalize(Vector3Subtract(player->GetPosition(), position));
    position =
        Vector3Add(position, Vector3Scale(forward, speed * GetFrameTime()));

    // Updating bounding box position
    boundingBox.min = (Vector3){position.x - size.width / 2.0f, position.y,
                                position.z - size.length / 2.0f};
    boundingBox.max =
        (Vector3){position.x + size.width / 2.0f, position.y + size.height,
                  position.z + size.length / 2.0f};

    // Updating Feelers
    // Center
    feelers.center.direction = forward;
    feelers.center.position = this->GetPosition();
    feelers.centerEndPoint = Vector3Add(
        feelers.center.position,
        Vector3Scale(feelers.center.direction, feelers.viewDistance));

    // Right
    feelers.right.direction =
        Vector3RotateByAxisAngle(forward, upAxis, -feelers.angle);
    feelers.right.position = this->GetPosition();
    feelers.rightEndPoint =
        Vector3Add(feelers.right.position,
                   Vector3Scale(feelers.right.direction, feelers.viewDistance));

    // Left
    feelers.left.direction =
        Vector3RotateByAxisAngle(forward, upAxis, feelers.angle);
    feelers.left.position = this->GetPosition();
    feelers.leftEndPoint =
        Vector3Add(feelers.left.position,
                   Vector3Scale(feelers.left.direction, feelers.viewDistance));

    // Checks collision between player and itself
    // also damages player
    if (CheckCollisionBoxes(player->GetBoundingBox(), boundingBox)) {
      player->TakeDamage(meleeDamage);
      position = previousPosition;
    }
  }
}

void Enemy::Draw(Player *player) {
  if (!dead) {
    BeginMode3D(player->camera);
    DrawBoundingBox(boundingBox, BLACK);
    DrawBillboardRec(
        player->camera, sprite.texture, sprite.source,
        Vector3Add(position, (Vector3){0.0f, size.height / 2.0f, 0.0f}),
        (Vector2){size.width * 2.0f, size.height}, sprite.tint);
    DrawRay(feelers.center, RED);
    DrawRay(feelers.right, RED);
    DrawRay(feelers.left, RED);
    DrawCube(position, 0.5f, 0.5f, 0.5f, RED);
    EndMode3D();
  }
}
// End Main Methods
// -------------------------------------------------------------
//
// Getters ------------------------------------------------------
Vector3 Enemy::GetPreviousPosition() { return previousPosition; }

BoundingBox Enemy::GetBoundingBox() { return boundingBox; }

// returns true center of enemy
Vector3 Enemy::GetPosition() {
  return (Vector3){position.x, size.height / 2.0f, position.z};
}

bool Enemy::IsDead() { return dead; }

Feelers Enemy::GetFeelers() { return feelers; }
// End Getters --------------------------------------------------
//
// Setters ------------------------------------------------------
void Enemy::SetPosition(Vector3 position) { this->position = position; }
void Enemy::SetXPosition(float x) { this->position.x = x; }
void Enemy::SetYPosition(float y) { this->position.x = y; }
void Enemy::SetZPosition(float z) { this->position.x = z; }
// End Setters ----------------------------------------------------
//
// Helper Methods -------------------------------------------------
void Enemy::SavePosition() { previousPosition = position; }

void Enemy::MoveLeft() {
  std::cout << "MOVING LEFT" << std::endl;
  Vector3 newDir = Vector3RotateByAxisAngle(forward, upAxis, 45.0f);
  position = Vector3Add(position, Vector3Scale(newDir, speed * GetFrameTime()));
}

void Enemy::MoveRight() {
  std::cout << "MOVING RIGHT" << std::endl;
  Vector3 newDir = Vector3RotateByAxisAngle(forward, upAxis, -45.0f);
  position = Vector3Add(position, Vector3Scale(newDir, speed * GetFrameTime()));
}

void Enemy::SlowDown() {
  std::cout << "SLOWING DOWN" << std::endl;
  timer.Start(1.0f);
}

void Enemy::ResetSpeed() { speed = 2.0f; }
// End Helper Methods --------------------------------------------------
} // namespace Entities
