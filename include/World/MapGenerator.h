#pragma once
#include "raymath.h"

#define MAP_SIZE 32

namespace World {
class MapGenerator {
public:
  MapGenerator();
  // TODO: add public methods here
private:
    int map[MAP_SIZE][MAP_SIZE];
    int heightMap[MAP_SIZE][MAP_SIZE];
};
} // namespace World
