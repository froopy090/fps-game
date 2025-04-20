#pragma once

#include <Registry.h>
#include <systems/System.h>
#include <Component.h>

class CollisionSystem : public System {
public:
  void Update(Registry &registry) override;
};
