#pragma once
#include "Entities/Player.h"
#include "raylib.h"

namespace Utility {
inline bool HitscanIntersectsBox(Entities::Player *player, BoundingBox box) {
  if (player->isShooting && GetRayCollisionBox(player->GetRay(), box).hit) {
    return true;
  } else {
    return false;
  }
}
} // namespace Utility
