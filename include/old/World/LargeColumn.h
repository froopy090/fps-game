#pragma once
#include "World/BaseObjects.h"
#include "raylib.h"
#include <memory>

namespace World {
class LargeColumn : public Cube {
public:
  LargeColumn(Vector3 position);

private:
  static std::unique_ptr<WorldTexture> texture;
};
} // namespace World
