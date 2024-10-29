#pragma once
#include "World/WorldDefinitions.h"

namespace World {
class MapGenerator {
public:
  MapGenerator();
  // TODO: add public methods here
private:
  int map[MAP_SIZE][MAP_SIZE];
};
} // namespace World
