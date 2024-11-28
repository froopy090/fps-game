#pragma once
#include "World/WorldDefinitions.h"
#include "raylib.h"
#include <memory>

namespace World {
class Cube {
public:
  Cube();
  // TODO: add this destructor
  // once room class is using unique pointers
  /*~Cube();*/
  Cube(Vector3 position);
  Cube(Vector3 position, Vector3 size);
  void Draw();
  void DrawCubeTexture();

  // Getters
  Vector3 GetPosition();
  Vector3 GetSize();
  Color GetColor();
  BoundingBox GetBoundingBox();

  // Setters
  void SetPosition(Vector3 position);
  void SetSize(Vector3 size);
  void SetColor(Color color);

  // Helper Functions
  void SetBoundingBox();

protected:
  Vector3 position;
  Vector3 size;
  Color color;
  BoundingBox box;

private:
  static std::shared_ptr<WorldTexture> texture;
};

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
