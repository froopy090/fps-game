#pragma once

#include <Component.h>
#include <Registry.h>
#include <raylib.h>
#include <raymath.h>
#include <systems/System.h>

class ViewCameraSystem : public System {
public:
  void Update(Registry &registry) override;
};
