#include "Entities/Enemy.h"
#include "Entities/EntityDefinitions.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "iostream"
#include "raylib.h"
#include "raymath.h"
#include <algorithm>
#include <cctype>

namespace Entities {
// Main Methods -----------------------------------------------------------
Enemy::Enemy(Player *player, Vector3 position) {
  // Dimensions init
  size.x = 0.5f;
  size.y = 1.5f;
  size.z = 0.5f;

  // Sprite init
  sprite.texture = LoadTexture("DOOM_Enemy.png");
  sprite.source = (Rectangle){3, 1, 77, 90};
  sprite.tint = WHITE;

  // Position init
  // position = (Vector3){0.0f, 0.0f, -4.0f};
  this->position = position;
  previousPosition = position;
  upAxis = (Vector3){0.0f, 1.0f, 0.0f};

  // Bounding box init
  boundingBox.min =
      (Vector3){position.x - size.x / 2.0f, 0.0f, position.z - size.z / 2.0f};
  boundingBox.max =
      (Vector3){position.x + size.x / 2.0f, size.y, position.z + size.z / 2.0f};

  // Health  and state init
  health = 150.0f;
  // dead = false;
  state = ENEMY_CHASING;

  // Damage init
  meleeDamage = 25.0f;

  // Movement attributes init
  //  Forward-facing direction init (unit vector)
  forward = Vector3Zero();
  // Speed and velocity init
  speed = 3.0f;
  velocity = Vector3Zero();
  randomAngle = 0.0f;

  // Vision ray init
  visionRay.direction = Vector3Zero();
  visionRay.position = Vector3Zero();

  // gravity and plane collision init
  planeCollision = true;
  rayHasCollided = false;
  gravity = -10.0f;
}

Enemy::~Enemy() { UnloadTexture(sprite.texture); }

void Enemy::Event() {
  // TODO: add event function
  if (!(state == ENEMY_DEAD)) {
  }
}

void Enemy::Update(Player *player, Pistol *pistol) {
  // only update enemy if it's dead
  if (!(state == ENEMY_DEAD)) {
    // Save position before updating
    this->SavePosition();

    // Checks collision between player hitscan ray and Enemy bounding box
    if (Utility::HitscanIntersectsBox(player, this)) {
      // Takes damage
      health -= pistol->GetDamage();
    }

    // Checking health
    if (health <= 0.0f) {
      // dead = true;
      state = ENEMY_DEAD;
      sprite.tint = BLANK;
    }

    // Movement Update
    float distanceFromPlayer =
        Vector3Distance(position, player->camera.position);
    // always keep the forward vector pointed towards player by default
    forward =
        Vector3Normalize(Vector3Subtract(player->GetPosition(), position));
    switch (state) {
    case ENEMY_CHASING:
      //  move towards player
      position =
          Vector3Add(position, Vector3Scale(forward, speed * GetFrameTime()));
      break;
    case ENEMY_IDLE:
      // if enemy is close enough, chase player
      if (distanceFromPlayer < 5.0f) {
        state = ENEMY_CHASING;
        break;
      }

      movementTimer.Update();
      //  if timer hasn't finished, keep chasing player
      //  else stop moving
      if (!movementTimer.Finished()) {
        position =
            Vector3Add(position, Vector3Scale(forward, speed * GetFrameTime()));
      } else {
        // position = previousPosition;
        //  generate a random angle to go in when the timer starts
        //  move in that direction until timer runs out
        searchTimer.Update();
        if (!searchTimer.Active()) {
          searchTimer.Start(5.0f);
          randomAngle = GetRandomValue(-180, 180);
        }
        forward = Vector3RotateByAxisAngle(forward, upAxis, randomAngle);
        position =
            Vector3Add(position, Vector3Scale(forward, speed * GetFrameTime()));
      }
      break;
    }

    // gravity being applied always, regardless of state
    position.y += gravity * GetFrameTime();
    if (planeCollision) {
      position.y = previousPosition.y;
    }

    // velocity Update
    velocity = Vector3Subtract(position, previousPosition);

    // Updating bounding box position
    boundingBox.min = (Vector3){position.x - size.x / 2.0f, position.y,
                                position.z - size.z / 2.0f};
    boundingBox.max = (Vector3){position.x + size.x / 2.0f, position.y + size.y,
                                position.z + size.z / 2.0f};

    // Vision ray Update
    visionRay.direction = forward;
    visionRay.position = position;

    // Checks collision between player and itself
    // also damages player
    if (CheckCollisionBoxes(player->GetBoundingBox(), boundingBox)) {
      player->TakeDamage(meleeDamage);
      position = previousPosition;
    }
  }
}

void Enemy::Draw(Player *player) {
  if (!(state == ENEMY_DEAD)) {
    BeginMode3D(player->camera);
    DrawBoundingBox(boundingBox, BLACK);
    DrawBillboardRec(
        player->camera, sprite.texture, sprite.source,
        Vector3Add(position, (Vector3){0.0f, position.y + size.y / 2.0f, 0.0f}),
        (Vector2){size.x * 2.0f, size.y}, sprite.tint);
    // draw vision ray for debug
    DrawRay(visionRay, RED);
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
  return (Vector3){position.x, size.y / 2.0f, position.z};
}

Ray Enemy::GetRay() { return visionRay; }

Vector3 Enemy::GetSize() { return size; }

Vector3 Enemy::GetVelocity() { return velocity; }

bool Enemy::RayHasCollided() { return rayHasCollided; }

EnemyState Enemy::GetState() { return state; }
//  End Getters --------------------------------------------------
//
//  Setters ------------------------------------------------------
void Enemy::SetPosition(Vector3 position) { this->position = position; }
void Enemy::SetXPosition(float x) { this->position.x = x; }
void Enemy::SetYPosition(float y) { this->position.y = y - size.y; }
void Enemy::SetZPosition(float z) { this->position.z = z; }

void Enemy::SetPlaneCollision(bool b) { this->planeCollision = b; }

void Enemy::SetChasePlayer() {
  state = ENEMY_CHASING;
  // movementTimer.Start(3.0f);
}

void Enemy::SetIdle() {
  if (!movementTimer.Active()) {
    movementTimer.Start(5.0f);
  }
  // std::cout << "idle" << std::endl;
  state = ENEMY_IDLE;
}

void Enemy::SetRayHasCollided(bool b) { this->rayHasCollided = b; }
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

void Enemy::ResetSpeed() { speed = 2.0f; }
// End Helper Methods --------------------------------------------------
} // namespace Entities
