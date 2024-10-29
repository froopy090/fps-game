#pragma once
#include "raylib.h"

namespace World {
class Plane {
public:
  Plane(Vector3 position);
  void Draw();

  // Getters
  Vector3 GetPosition();
  Vector2 GetSize();
  Color GetColor();
  BoundingBox GetBoundingBox();
  // Setters
  void SetPosition(Vector3 position);
  void SetSize(Vector2 size);
  void SetColor(Color color);
  void SetBoundingBox(BoundingBox box);

private:
  Vector3 position;
  Vector2 size;
  Color color;
  BoundingBox box;
};
} // namespace World
