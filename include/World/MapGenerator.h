#pragma once

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
