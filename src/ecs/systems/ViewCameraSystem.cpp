#include "systems/ViewCameraSystem.h"

void ViewCameraSystem::Update(Registry &registry) {
  auto &cameras = registry.getMap<ViewCameraComponent>();

  for (auto &[entity, camera] : cameras) {
    // Update position
    camera.camera.position =
        registry.getComponent<TransformComponent>(entity).position;

    // Update camera target to be a point directly in front of camera
    Vector3 forward = Vector3Normalize(
        Vector3Subtract(camera.camera.target, camera.camera.position));
    camera.camera.target =
        Vector3Add(camera.camera.position, Vector3Scale(forward, 100.0f));

    UpdateCamera(&camera.camera, camera.cameraMode);
  }
}
