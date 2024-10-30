#include "Entities/Player.h"
#include "Utility/Timer.h"
#include "raylib.h"
#include "raymath.h"

namespace Entities {
Player::Player() {
  // Player size init
  size.length = 0.5f;
  size.height = 1.0f;
  size.width = 0.5f;

  // Camera init
  camera = {0};
  camera.position = (Vector3){0.0f, size.height, 7.0f};
  camera.target = Vector3Zero();           // camera looking at point
  camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // camera up vector
  camera.fovy = 90.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  cameraMode = CAMERA_FIRST_PERSON;
  DisableCursor(); // limit cursor movement to window

  // Bounding box init
  boundingBox.min = (Vector3){camera.position.x - size.width / 2.0f, 0.0f,
                              camera.position.z - size.length / 2.0f};
  boundingBox.max =
      (Vector3){camera.position.x + size.width / 2.0f, camera.position.y,
                camera.position.z + size.length / 2.0f};

  previousPosition = camera.position;
  isShooting = false;

  // Gravity physics
  gravity = -10.0f;
  jumpVelocity = 0.0f;
  isJumping = false;
  planeCollision = false;

  // Health init
  health = 100.0f;
}

void Player::Event() {
  // no clip for debugging
  if (IsKeyPressed(KEY_ZERO)) {
    cameraMode = CAMERA_FREE;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // reset roll
  }

  if (IsKeyPressed(KEY_ONE)) {
    cameraMode = CAMERA_FIRST_PERSON;
    camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // reset roll
  }

  // shooting pistol
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    isShooting = true;
    timer.Start(0.04f);
  }

  // jumping
  if (IsKeyPressed(KEY_SPACE) && !isJumping) {
    jumpVelocity = 4.0f;
    isJumping = true;
  }
}

void Player::Update() {
  // Save player position before updating
  this->SavePosition();

  // Update Camera postion
  UpdateCamera(&camera, cameraMode);

  if (cameraMode != CAMERA_FREE) {
    // Update hitscan timer
    timer.Update();
    if (timer.Finished()) {
      isShooting = false;
    }

    // Update camera target to be a point directly in front of camera
    Vector3 forward =
        Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    camera.target = Vector3Add(camera.position, Vector3Scale(forward, 100.0f));

    // Jumping
    if (isJumping) {
      jumpVelocity += gravity * GetFrameTime();
    } else {
      // gravity is always in effect
      jumpVelocity = gravity; // clearly how physics work
    }

    camera.position.y += jumpVelocity * GetFrameTime();

    if (jumpVelocity < 0.0f && planeCollision) {
      camera.position.y = size.height;
      isJumping = false;
    }

    // Update position
    if (cameraMode == CAMERA_FIRST_PERSON) {
      boundingBox.min = (Vector3){camera.position.x - size.width / 2.0f,
                                  camera.position.y - size.height,
                                  camera.position.z - size.length / 2.0f};
      boundingBox.max =
          (Vector3){camera.position.x + size.width / 2.0f, camera.position.y,
                    camera.position.z + size.length / 2.0f};
    }
  }
}

void Player::Draw() {
  BeginMode3D(camera);
  DrawBoundingBox(boundingBox, DARKPURPLE);
  if (isShooting) {
    Ray hitscanRay = {camera.position, Vector3Normalize(Vector3Subtract(
                                           camera.target, camera.position))};
    DrawRay(hitscanRay, RED);
  }
  EndMode3D();
}

// Getters
// returns center of bounding box position (NOT the camera position)
Vector3 Player::GetPosition() {
  return Vector3Subtract(camera.position,
                         (Vector3){0.0f, size.height / 2.0f, 0.0f});
}
Ray Player::GetRay() {
  Ray hitscanRay = {camera.position, Vector3Normalize(Vector3Subtract(
                                         camera.target, camera.position))};
  return hitscanRay;
}
BoundingBox Player::GetBoundingBox() { return boundingBox; }
Vector3 Player::GetPreviousPosition() { return previousPosition; }
float Player::GetHealth() { return health; }
bool Player::IsShooting() { return isShooting; }

// Setters
void Player::SavePosition() { previousPosition = camera.position; }
void Player::TakeDamage(float damage) {
  if (health > 0.0f) {
    health -= damage * GetFrameTime();
  }
}
void Player::SetPlaneCollision(bool b) { planeCollision = b; }
} // namespace Entities
