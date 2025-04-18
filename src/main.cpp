#include "ecs/ViewCameraSystem.h"
#include <GameState.h>
#include <ecs/ModelRenderSystem.h>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <resource_dir.h>

// Forward declarations
void InitGame(GameState *game);
void UpdateGame(GameState *game);
void DrawGame(GameState *game);
void CloseGame(GameState *game);

// Main ---------------------------------------------------
int main() {
  // Init
  GameState game;
  InitGame(&game);

  // Game loop
  while (!WindowShouldClose()) {
    UpdateGame(&game);
    DrawGame(&game);
  }

  // Shutdown
  CloseGame(&game);
  return 0;
}

// --------------------------------------------------------

// Helper functions
void InitGame(GameState *game) {
  // Window
  InitWindow(game->screenWidth, game->screenHeight, "ECS example");

  SearchAndSetResourceDir("resources");

  // Loading entities
  game->registry.addComponent(
      game->playerEntity,
      ViewCameraComponent{
          .camera = Camera3D{.position = (Vector3){0.0f, 2.0f, 4.0f},
                             .target = (Vector3){0.0f, 2.0f, 0.0f},
                             .up = (Vector3){0.0f, 1.0f, 0.0f},
                             .fovy = 60.0f,
                             .projection = CAMERA_PERSPECTIVE},
          .cameraMode = CAMERA_FIRST_PERSON,
      });

  Model model = LoadModel("simple_plane.obj");
  Texture2D texture = LoadTexture("concrete.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

  Vector3 position = {0.0f, 0.0f, 0.0f};
  BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);
  bounds.max = Vector3Add(position, bounds.max);
  bounds.min = Vector3Add(position, bounds.min);

  ModelComponent modelComponent;
  modelComponent.model = model;
  modelComponent.texture = texture;
  modelComponent.position = position;
  modelComponent.bounds = bounds;

  game->registry.addComponent(game->planeEntity, modelComponent);

  DisableCursor();
  SetTargetFPS(144);

  // Adding systems to vector
  game->updateSystems.push_back(new ViewCameraSystem());
  game->renderSystems.push_back(new ModelRenderSystem());
}

void UpdateGame(GameState *game) {
  for (auto &system : game->updateSystems) {
    system->Update(game->registry);
  }
}

void DrawGame(GameState *game) {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawFPS(10, 10);

  BeginMode3D(
      game->registry.getComponent<ViewCameraComponent>(game->playerEntity)
          .camera);

  for (auto &system : game->renderSystems) {
    system->Update(game->registry);
  }

  // DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
  //           LIGHTGRAY); // Draw ground
  // DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
  //          BLUE); // Draw a blue wall
  // DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
  //          LIME); // Draw a green wall
  // DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
  //          GOLD); // Draw a yellow wall
  EndMode3D();
  EndDrawing();
}

void CloseGame(GameState *game) {
  // Unloading resources first
  for (auto &[entity, modelComp] : game->registry.getMap<ModelComponent>()) {
    std::cout << "Unloading model with meshcount: " << modelComp.model.meshCount
              << " , texture id: " << modelComp.texture.id << std::endl;

    if (modelComp.texture.id > 0)
      UnloadTexture(modelComp.texture);
    if (modelComp.model.meshCount > 0)
      UnloadModel(modelComp.model);
  }

  // Deleting systems
  for (auto &system : game->updateSystems) {
    delete system;
  }
  for (auto &system : game->renderSystems) {
    delete system;
  }

  // Closing window
  CloseWindow();
}
