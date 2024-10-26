#pragma once
#include "raylib.h"

namespace Entities {
struct EnemySprite {
  Texture2D texture;
  Rectangle source;
  Color tint;
};

struct Feelers {
  Ray right;
  Vector3 rightEndPoint;
  Ray center;
  Vector3 centerEndPoint;
  Ray left;
  Vector3 leftEndPoint;
  float viewDistance;
  float angle;
};

struct Sprite{
  Rectangle source;
  Rectangle destination;
  Vector2 origin;
  float rotation;
  Color tint;
};

struct Size {
  float width;
  float height;
  float length;
};

typedef enum State{IDLE, FIRING, RELOADING} State;
} // namespace Entities
