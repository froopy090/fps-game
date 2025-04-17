#include "ecs/ViewCameraSystem.h"

void ViewCameraSystem::Update(Registry &registry) {
  auto &cameras = registry.getMap<ViewCameraComponent>();

  for (auto &[entity, camera] : cameras) {
    UpdateCamera(&camera.camera, camera.cameraMode);
  }
}
