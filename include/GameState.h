#pragma once

#include <ecs/Registry.h>
#include <ecs/System.h>
#include <vector>

struct GameState {
  // Window settings
  const int screenWidth = 800;
  const int screenHeight = 450;

  // Registry
  Registry registry;

  // Entities
  Entity playerEntity = registry.createEntity();
  Entity planeEntity = registry.createEntity();

  // Systems
  std::vector<System *> updateSystems;
  std::vector<System *> renderSystems;
};
