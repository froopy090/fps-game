#include "World/LargeColumn.h"
#include "World/WorldDefinitions.h"
#include "raymath.h"

namespace World {
std::unique_ptr<WorldTexture> LargeColumn::texture = nullptr;

LargeColumn::LargeColumn(Vector3 position) {
  // Init
  this->position =
      Vector3Add(position, (Vector3){0.0f, COLUMN_HEIGHT / 2.0f, 0.0f});
  size = (Vector3){TILE_SIZE, COLUMN_HEIGHT, TILE_SIZE};
  color = DARKGRAY;
  box.min = (Vector3){position.x - size.x / 2.0f, position.y,
                      position.z - size.z / 2.0f};
  box.max = (Vector3){position.x + size.x / 2.0f, position.y + size.y,
                      position.z + size.z / 2.0f};
  if (!texture) {
    texture = std::make_unique<WorldTexture>();
    texture->texture = LoadTexture("metal_dark.png");
  }
}
} // namespace World
