#include "World/Cube.h"
#include "World/WorldDefinitions.h"
#include "raylib.h"
#include "raymath.h"

namespace World {
Cube::Cube(Vector3 position) {
  // Init
  this->position =
      Vector3Add(position, (Vector3){0.0f, WALL_HEIGHT / 2.0f, 0.0f});
  size = (Vector3){TILE_SIZE, WALL_HEIGHT, TILE_SIZE};
  color = DARKGRAY;
  box.min =
      (Vector3){position.x - size.x / 2.0f, 0.0f, position.z - size.z / 2.0f};
  box.max =
      (Vector3){position.x + size.x / 2.0f, size.y, position.z + size.z / 2.0f};
}

void Cube::Draw() {
  DrawCubeV(position, size, color);
  DrawBoundingBox(box, BLACK);
}

// Getters
Vector3 Cube::GetPosition() { return position; }

Vector3 Cube::GetSize() { return size; }

Color Cube::GetColor() { return color; }

BoundingBox Cube::GetBoundingBox() { return box; }

// Setters
void Cube::SetPosition(Vector3 position) { this->position = position; }

void Cube::SetSize(Vector3 size) { this->size = size; }

void Cube::SetColor(Color color) { this->color = color; }

void Cube::SetBoundingBox(BoundingBox box) { this->box = box; }
} // namespace World
