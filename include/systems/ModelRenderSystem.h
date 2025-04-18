#pragma once

#include <Component.h>
#include <Registry.h>
#include <systems/System.h>
#include <raylib.h>

class ModelRenderSystem : public System {
public:
  void Update(Registry &registry) override;
};
