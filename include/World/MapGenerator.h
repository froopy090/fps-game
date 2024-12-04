#pragma once
#include "World/WorldDefinitions.h"

namespace World {
class MapGenerator {
public:
  MapGenerator();
  // TODO: add public methods here
  void Update();
  void Draw();

private:
  static const int map[MAP_SIZE][MAP_SIZE];
};
} // namespace World
