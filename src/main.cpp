#include "ecs/Component.h"
#include "ecs/Entity.h"
#include "ecs/Registry.h"
#include "ecs/System.h"
#include "ecs/ViewCameraSystem.h"
#include <raylib.h>

int main() {
  // Init
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "ECS example");

  Registry registry;
  Entity player = registry.createEntity();
  ViewCamera playerCamera;
  playerCamera.camera = {0};
  playerCamera.camera.position = (Vector3){0.0f, 2.0f, 4.0f};
  playerCamera.camera.target = (Vector3){0.0f, 2.0f, 0.0f};
  playerCamera.camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  playerCamera.camera.fovy = 60.0f;
  playerCamera.camera.projection = CAMERA_PERSPECTIVE;
  playerCamera.cameraMode = CAMERA_FIRST_PERSON;
  registry.addComponent(player, playerCamera);

  DisableCursor();
  SetTargetFPS(60);

  std::vector<System *> gameSystems;
  gameSystems.push_back(new ViewCameraSystem());

  // Game loop
  while (!WindowShouldClose()) {
    // Update
    for (auto &system : gameSystems) {
      system->Update(registry);
    }

    // Draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(registry.getComponent<ViewCamera>(player).camera);

    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
              LIGHTGRAY); // Draw ground
    DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
             BLUE); // Draw a blue wall
    DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
             LIME); // Draw a green wall
    DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
             GOLD); // Draw a yellow wall
    EndMode3D();
    EndDrawing();
  }

  // De-initialization
  CloseWindow();
  for (auto &system : gameSystems) {
    delete system;
  }

  return 0;
}
