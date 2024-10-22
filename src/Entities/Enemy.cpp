#include "Entities/Enemy.h"
#include "raylib.h"

namespace Entities {
Enemy::Enemy() {
  // Dimensions init
  size.width = 0.5f;
  size.height = 1.0f;
  size.length = 0.5f;

  // Position init
  position = (Vector3){0.0f, size.height / 2.0f, 10.0f};

  // Bounding box init
  boundingBox.min =
      (Vector3){position.x - size.width / 2.0f, position.y - size.height / 2.0f,
                position.z - size.length / 2.0f};
  boundingBox.max =
      (Vector3){position.x + size.width / 2.0f, position.y + size.height / 2.0f,
                position.z + size.length / 2.0f};

  // Health init
  health = 100.0f;
}

void Enemy::Event() {
  // TODO: add event function
}

void Enemy::Update() {
  // TODO: add update function
}

void Enemy::Draw() {
  // TODO: add draw function
}
} // namespace Entities
