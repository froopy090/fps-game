#include "World/Floor.h"
#include "World/WorldDefinitions.h"

namespace World {
Floor::Floor(Vector3 position) {
  // Init
  this->position = position;
  dimension = (Vector2){TILE_SIZE, TILE_SIZE};
  color = GRAY;
  box.min = (Vector3){-dimension.x / 2.0f, position.y, -dimension.y / 2.0f};
  box.max = (Vector3){dimension.x / 2.0f, position.y, dimension.y / 2.0f};
}

void Floor::Draw() {
  // TODO: add draw functions here
}
} // namespace World
