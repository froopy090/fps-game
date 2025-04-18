#include <Component.h>
#include <Game.h>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <resource_dir.h>
#include <systems/ModelRenderSystem.h>
#include <systems/ViewCameraSystem.h>

void InitGame(GameState *game) {
  // Window
  InitWindow(game->screenWidth, game->screenHeight, "ECS example");

  SearchAndSetResourceDir("resources");

  // Loading entities
  game->registry.addComponent(
      game->playerEntity,
      TransformComponent{.position = (Vector3){0.0f, 2.0f, 4.0f}});
  game->registry.addComponent(game->playerEntity,
                              VelocityComponent{.velocity = Vector3Zero()});
  game->registry.addComponent(
      game->playerEntity,
      ViewCameraComponent{
          .camera = Camera3D{.position = game->registry
                                             .getComponent<TransformComponent>(
                                                 game->playerEntity)
                                             .position,
                             .target = (Vector3){0.0f, 2.0f, 0.0f},
                             .up = (Vector3){0.0f, 1.0f, 0.0f},
                             .fovy = 60.0f,
                             .projection = CAMERA_PERSPECTIVE},
          .cameraMode = CAMERA_FIRST_PERSON,
      });
  // TODO: fix this later
  game->registry.addComponent(game->playerEntity, ColliderComponent{});

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

  game->registry.addComponent(game->planeEntity, modelComponent);
  game->registry.addComponent(game->planeEntity,
                              TransformComponent{.position = position});
  game->registry.addComponent(
      game->planeEntity, ColliderComponent{.bounds = bounds, .isStatic = true});

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
