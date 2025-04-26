#include <Component.h>
#include <Game.h>
#include <entities/EnvironmentFactory.h>
#include <entities/PlayerFactory.h>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <resource_dir.h>
#include <systems/CollisionSystem.h>
#include <systems/ModelRenderSystem.h>
#include <systems/PhysicsSystem.h>
#include <systems/UpdateColliderSystem.h>
#include <systems/ViewCameraSystem.h>
#include <systems/debug/DebugColliderRenderSystem.h>

void InitGame(GameState *game) {
  // Window
  InitWindow(game->screenWidth, game->screenHeight, "ECS example");

  SearchAndSetResourceDir("resources");

  game->playerEntity = CreatePlayer(game->registry);
  game->planeEntity = CreatePlane(game->registry);

  DisableCursor();
  SetTargetFPS(144);

  // Adding systems to vector
  game->updateSystems.push_back(new ViewCameraSystem());
  game->updateSystems.push_back(new PhysicsSystem());
  game->updateSystems.push_back(new CollisionSystem());
  game->updateSystems.push_back(new UpdateColliderSystem());

  game->renderSystems.push_back(new ModelRenderSystem());
  game->renderSystems.push_back(new DebugColliderRenderSystem());
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
