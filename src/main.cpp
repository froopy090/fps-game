#include "ecs/Component.h"
#include "ecs/Entity.h"
#include "ecs/Registry.h"
#include "ecs/System.h"
#include "ecs/ViewCameraSystem.h"
#include <raylib.h>

// Gobal variables ----------------------------------------
// Window
const int screenWidth = 800;
const int screenHeight = 450;

// Core
// Registry
Registry registry;

// Entities
Entity player = registry.createEntity();

// Systems
std::vector<System *> gameSystems;

// --------------------------------------------------------

// Forward declarations
void InitGame();
void UpdateGame();
void DrawGame();
void CloseGame();

// Main ---------------------------------------------------
int main() {
  // Init
  InitGame();

  // Game loop
  while (!WindowShouldClose()) {
    UpdateGame();
    DrawGame();
  }

  // Shutdown
  CloseGame();
  return 0;
}

// --------------------------------------------------------

// Helper functions
void InitGame() {
  InitWindow(screenWidth, screenHeight, "ECS example");

  registry.addComponent(
      player, ViewCamera{
                  .camera = Camera3D{.position = (Vector3){0.0f, 2.0f, 4.0f},
                                     .target = (Vector3){0.0f, 2.0f, 0.0f},
                                     .up = (Vector3){0.0f, 1.0f, 0.0f},
                                     .fovy = 60.0f,
                                     .projection = CAMERA_PERSPECTIVE},
                  .cameraMode = CAMERA_FIRST_PERSON,
              });

  DisableCursor();
  SetTargetFPS(60);

  gameSystems.push_back(new ViewCameraSystem());
}

void UpdateGame() {
  for (auto &system : gameSystems) {
    system->Update(registry);
  }
}

void DrawGame() {
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

void CloseGame() {
  CloseWindow();
  for (auto &system : gameSystems) {
    delete system;
  }
}
