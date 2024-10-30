#include "World/Plane.h"
#include "World/WorldDefinitions.h"
#include "raylib.h"

namespace World {
Plane::Plane(Vector3 position) {
  // Init
  this->position = position;
  size = (Vector2){TILE_SIZE, TILE_SIZE};
  color = GRAY;
  box.min = (Vector3){position.x - size.x / 2.0f, position.y,
                      position.z - size.y / 2.0f};
  box.max = (Vector3){position.x + size.x / 2.0f, position.y,
                      position.z + size.y / 2.0f};
}

void Plane::Draw() {
  DrawPlane(position, size, color);
  DrawBoundingBox(box, BLACK);
}

// Getters
Vector3 Plane::GetPosition() { return position; }

Vector2 Plane::GetSize() { return size; }

Color Plane::GetColor() { return color; }

BoundingBox Plane::GetBoundingBox() { return box; }

// Setters
void Plane::SetPosition(Vector3 position) { this->position = position; }

void Plane::SetSize(Vector2 size) { this->size = size; }

void Plane::SetColor(Color color) { this->color = color; }

void Plane::SetBoundingBox(BoundingBox box) { this->box = box; }
} // namespace World
