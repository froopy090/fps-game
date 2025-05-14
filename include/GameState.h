#pragma once

#include <Registry.h>
#include <systems/System.h>
#include <vector>

struct GameState {
  // Window settings
  const int screenWidth = 800;
  const int screenHeight = 450;

  // Registry
  Registry registry;

  // Entities
  Entity playerEntity;
  Entity planeEntity;
  Entity planeEntity2;
  Entity cubeEntity;
  Entity cubeEntity2;
  Entity cubeEntity3;

  // Systems
  std::vector<System *> updateSystems;
  std::vector<System *> renderSystems;
};
