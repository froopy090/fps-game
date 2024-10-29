#include "World/Wall.h"
#include "World/WorldDefinitions.h"

namespace World {
Wall::Wall(Vector3 position) {
  // Init
  this->position = position;
  dimensions = (Vector3){TILE_SIZE, WALL_HEIGHT, TILE_SIZE};
  color = DARKGRAY;
  box.min = (Vector3){position.x - dimensions.x / 2.0f, 0.0f,
                      position.z - dimensions.z / 2.0f};
  box.max = (Vector3){position.x + dimensions.x / 2.0f, dimensions.y,
                      position.z + dimensions.z / 2.0f};
}

void Wall::Draw(){
    //TODO: add draw functions here
}
} // namespace World
