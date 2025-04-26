#pragma once

#include <Component.h>
#include <Registry.h>
#include <systems/System.h>

class UpdateColliderSystem : public System {
public:
  void Update(Registry &registry) override;
};
