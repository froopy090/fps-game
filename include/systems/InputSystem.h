#pragma once

#include <Component.h>
#include <Registry.h>
#include <systems/System.h>
#include <raymath.h>

class InputSystem : public System {
public:
  void Update(Registry &registry) override;
};
