#include "Entities/Player.h"
#include "Utility/Timer.h"
#include "World/TestMap.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

namespace Entities {
Player::Player() {
  // Player size init
  size.length = 0.5f;
  size.height = 1.0f;
  size.width = 0.5f;

  // Camera init
  camera = {0};
  camera.position = (Vector3){0.0f, size.height, 4.0f};
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
}

void Player::Event() {
  // TODO input events
  if (IsKeyPressed(KEY_THREE)) {
    cameraMode = CAMERA_THIRD_PERSON;
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
  // TODO: add check with plane in the if statement to avoid spam jumping
  if (IsKeyPressed(KEY_SPACE) && !isJumping) {
    jumpVelocity = 4.0f;
    isJumping = true;
  }
}

void Player::Update(World::TestMap *testMap) {
  // Save player position before updating
  this->SavePosition();

  // Update hitscan timer
  timer.Update();
  if (timer.Finished()) {
    isShooting = false;
  }

  // Update Camera postion
  UpdateCameraPro(
      &camera,
      (Vector3){
          (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) *
                  0.1f - // Move forward-backward
              (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) * 0.1f,
          (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) * 0.1f - // Move right-left
              (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) * 0.1f,
          0.0f // Move up-down
      },
      (Vector3){
          GetMouseDelta().x * 0.05f, // Rotation: yaw
          GetMouseDelta().y * 0.05f, // Rotation: pitch
          0.0f                       // Rotation: roll
      },
      GetMouseWheelMove() * 2.0f); // Move to target (zoom)

  // Update camera target to be a point directly in front of camera
  Vector3 forward =
      Vector3Normalize(Vector3Subtract(camera.target, camera.position));
  camera.target = Vector3Add(camera.position, Vector3Scale(forward, 100.0f));

  // Jumping
  if (isJumping) {
    jumpVelocity += gravity * GetFrameTime();
  }
  else{
    jumpVelocity = gravity;
  }

  camera.position.y += jumpVelocity * GetFrameTime();

  if (jumpVelocity < 0.0f &&
      CheckCollisionBoxes(boundingBox, testMap->GetPlaneBoundingBox())) {
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

  if (cameraMode == CAMERA_THIRD_PERSON) {
    // TODO: update variables for third person POV
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

// returns camera position
Vector3 Player::GetPosition() { return camera.position; }

Ray Player::GetRay() {
  Ray hitscanRay = {camera.position, Vector3Normalize(Vector3Subtract(
                                         camera.target, camera.position))};
  return hitscanRay;
}

BoundingBox Player::GetBoundingBox() { return boundingBox; }

void Player::SavePosition() { previousPosition = camera.position; }

Vector3 Player::GetPreviousPosition() { return previousPosition; }
} // namespace Entities
