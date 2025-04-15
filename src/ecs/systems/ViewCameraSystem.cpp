#include "ecs/ViewCameraSystem.h"

void ViewCameraSystem::Update(Registry &registry) {
  auto &cameras = registry.getMap<ViewCamera>();

  for (auto &[entity, camera] : cameras) {
    UpdateCamera(&camera.camera, camera.cameraMode);
  }
}
