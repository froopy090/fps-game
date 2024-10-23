#pragma once
#include "raylib.h"
#include "Entities/Player.h"

namespace Entities {
class Enemy {
  struct Size {
    float width;
    float height;
    float length;
  };

public:
  Enemy();
  void Event();
  void Update();
  void Draw(Player *player);

private:
  Size size;
  Vector3 position;
  float health;
  BoundingBox boundingBox;
};
} // namespace Entities
