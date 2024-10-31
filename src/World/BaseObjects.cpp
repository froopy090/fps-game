#include "World/BaseObjects.h"
#include "World/WorldDefinitions.h"
#include "raymath.h"

namespace World {
Cube::Cube() {
  // default constructor
  position = Vector3Zero();
  size = Vector3Zero();
  color = BLACK;
  box.min = Vector3Zero();
  box.max = Vector3Zero();
}

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
