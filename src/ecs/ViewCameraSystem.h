#pragma once

#include "Component.h"
#include "Registry.h"
#include "System.h"
#include "raylib.h"

class ViewCameraSystem : public System {
  void Update(Registry &registry) override {
    auto &cameras = registry.getMap<ViewCamera>();

    for (auto &[entity, camera] : cameras) {
      UpdateCamera(&camera.camera, camera.cameraMode);
    }
  }
};
