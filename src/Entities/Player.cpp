#include "Entities/Player.h"
#include "Utility/Timer.h"
#include "raylib.h"
#include "raymath.h"

#include <iostream>

namespace Entities {
Player::Player() {
  // Player size init
  size.x = 0.5f;
  size.y = 1.0f;
  size.z = 0.5f;

  // init speed and sensitivity
  speed = 0.05f;
  mouseSensitivity = 0.3f;

  // Camera init
  camera = {0};
  camera.position = (Vector3){0.0f, size.y, 1.0f};
  camera.target = Vector3Zero();           // camera looking at point
  camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // camera up vector
  camera.fovy = 90.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  cameraMode = CAMERA_FIRST_PERSON;
  DisableCursor(); // limit cursor movement to window

  // Bounding box init
  boundingBox.min = (Vector3){camera.position.x - size.z / 2.0f, 0.0f,
                              camera.position.z - size.x / 2.0f};
  boundingBox.max =
      (Vector3){camera.position.x + size.z / 2.0f, camera.position.y,
                camera.position.z + size.x / 2.0f};

  previousPosition = camera.position;
  isShooting = false;

  // Gravity physics
  gravity = -10.0f;
  jumpVelocity = 0.0f;
  isJumping = false;
  planeCollision = false;

  // Health init
  health = 100.0f;

  // Stairs flag init
  isOnStair = false;
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
  if(cameraMode == CAMERA_FREE){
    UpdateCamera(&camera, cameraMode);
  }

  // only update the player if we're in first person POV
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
      camera.position.y = previousPosition.y;
      isJumping = false;
    }

    // Update Camera postion
    UpdateCameraPro(&camera,
                    (Vector3){(IsKeyDown(KEY_W) - IsKeyDown(KEY_S)) * speed,
                              (IsKeyDown(KEY_D) - IsKeyDown(KEY_A)) * speed,
                              0.0f},
                    (Vector3){GetMouseDelta().x * mouseSensitivity,
                              GetMouseDelta().y * mouseSensitivity, 0.0f},
                    0.0f);

    // Update position
    boundingBox.min =
        (Vector3){camera.position.x - size.z / 2.0f, camera.position.y - size.y,
                  camera.position.z - size.x / 2.0f};
    boundingBox.max =
        (Vector3){camera.position.x + size.z / 2.0f, camera.position.y,
                  camera.position.z + size.x / 2.0f};
  }

  // if player falls through map, reset position
  if (GetBoundingBox().min.y <= -30) {
    std::cerr << "PLAYER FELL through map" << std::endl;
    camera.position.y = size.y + 20;
  }
}

void Player::Draw() {
  BeginMode3D(camera);
  DrawBoundingBox(boundingBox, LIME);
  if (isShooting) {
    Ray hitscanRay = {camera.position, Vector3Normalize(Vector3Subtract(
                                           camera.target, camera.position))};
  }
  EndMode3D();
}

// Getters
// returns center of bounding box position (NOT the camera position)
Vector3 Player::GetPosition() {
  return Vector3Subtract(camera.position, (Vector3){0.0f, size.y / 2.0f, 0.0f});
}

Vector3 Player::GetSize() { return size; }

Ray Player::GetRay() {
  Ray hitscanRay = {camera.position, Vector3Normalize(Vector3Subtract(
                                         camera.target, camera.position))};
  return hitscanRay;
}
BoundingBox Player::GetBoundingBox() { return boundingBox; }
Vector3 Player::GetPreviousPosition() { return previousPosition; }
float Player::GetHealth() { return health; }
bool Player::IsShooting() { return isShooting; }
bool Player::GetStairFlag() { return isOnStair; }

// Setters
void Player::SavePosition() { previousPosition = camera.position; }

void Player::TakeDamage(float damage) {
  if (health > 0.0f) {
    health -= damage * GetFrameTime();
  }
}
void Player::SetPlaneCollision(bool b) { planeCollision = b; }

void Player::SetStairFlag(bool b) { isOnStair = b; }
} // namespace Entities
