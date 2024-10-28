#pragma once
#include "raymath.h"

namespace World {
class MapGenerator {
public:
  MapGenerator();
  // TODO: add public methods here
private:
  Matrix map;
  Matrix heightMap;
};
} // namespace World
