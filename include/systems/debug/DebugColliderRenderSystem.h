#pragma once

#include <Component.h>
#include <Registry.h>
#include <systems/System.h>

class DebugColliderRenderSystem : public System {
public:
  void Update(Registry &registry) override;
};
