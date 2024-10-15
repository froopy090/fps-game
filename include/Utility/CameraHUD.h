#pragma once
#include "raylib.h"
#include "Entities/Player.h"

namespace Utility {
class CameraHUD {
public:
  void Draw(Entities::Player *player);
};
} // namespace Utility
