#include "Entities/Player.h"
#include "raylib.h"
#include "raymath.h"

namespace Entities {
Player::Player() {
  // PlayerCube init
  playerCube.color = GREEN;
  playerCube.width = 1.0f;
  playerCube.height = 2.0f;
  playerCube.length = 1.0f;
  playerCube.position = (Vector3){0, playerCube.height/2, 4}; // spawn

  // Camera init
  camera = {0};
  camera.position = Vector3Add(playerCube.position, (Vector3){0,playerCube.height/2,0});
  camera.target = Vector3Zero();           // camera looking at point
  camera.up = (Vector3){0.0f, 1.0f, 0.0f}; // camera up vector
  camera.fovy = 90.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  cameraMode = CAMERA_FREE;
  DisableCursor(); // limit cursor movement to window
}

void Player::Event() {
  // TODO input events
}

void Player::Update() {
  // TODO: update player variables here
  UpdateCamera(&camera, cameraMode);
  playerCube.position.x = camera.position.x;
  playerCube.position.z = camera.position.z;
}

void Player::Draw() {
  // TODO: draw player here
  BeginMode3D(camera);
  DrawCube(playerCube.position, playerCube.width, playerCube.height,
           playerCube.length, playerCube.color);
  DrawCubeWires(playerCube.position, playerCube.width, playerCube.height,
                playerCube.length, DARKPURPLE);
  EndMode3D();
}
} // namespace Entities
