#pragma once

#include <ecs/Component.h>
#include <ecs/Registry.h>
#include <ecs/System.h>
#include <raylib.h>

class ModelRenderSystem : public System {
public:
  void Update(Registry &registry) override;
};
