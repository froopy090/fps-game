#pragma once
#include "Cube.h"
#include "raylib.h"

namespace World {
class LargeColumn : public Cube {
public:
  LargeColumn(Vector3 position);
};
} // namespace World
