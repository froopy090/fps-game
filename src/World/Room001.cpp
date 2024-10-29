#include "World/Room001.h"

namespace World {
const int Room001::roomMatrix[ROOM_SIZE][ROOM_SIZE] = {{1, 1, 1, 1, 1},
                                                       {1, 0, 0, 0, 0},
                                                       {1, 0, 1, 0, 1},
                                                       {1, 0, 0, 0, 1},
                                                       {1, 1, 1, 1, 1}};
Room001::Room001() {
  // Calculate center of matrix and offset for tiles
  int center = ROOM_SIZE / 2; // 5/2 = 2

  // Populate floors and walls
  for (int i = 0; i < ROOM_SIZE; i++) {
    for (int j = 0; j < ROOM_SIZE; j++) {
      // calulating position of tile
      float x = (i - center) * (-TILE_SIZE);
      float z = (j - center) * (-TILE_SIZE);
      Vector3 position = {x, 0.0f, z};

      if (roomMatrix[i][j] == 0) {
        floors.emplace_back(position);
      } else if (roomMatrix[i][j] == 1) {
        walls.emplace_back(position);
      }
    }
  }
}

void Room001::Draw() {
  // TODO: draw functions here
  for (Plane &floor : floors) {
    floor.Draw();
  }
  for (Cube &wall : walls) {
    wall.Draw();
  }
}
} // namespace World
