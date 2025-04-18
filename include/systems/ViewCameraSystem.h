#pragma once

#include "Component.h"
#include "Registry.h"
#include "System.h"
#include "raylib.h"

class ViewCameraSystem : public System {
  void Update(Registry &registry) override;
};
