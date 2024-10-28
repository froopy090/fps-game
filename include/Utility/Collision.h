#pragma once
#include "Entities/Player.h"
#include "World/WorldDefinitions.h"
#include "raylib.h"

namespace Utility {
inline bool HitscanIntersectsBox(Entities::Player *player, BoundingBox box) {
  if (player->IsShooting() && GetRayCollisionBox(player->GetRay(), box).hit) {
    return true;
  } else {
    return false;
  }
}

inline BoundingBox InitPlaneBoundingBox(World::Plane p) {
  BoundingBox bb;
  bb.min =
      (Vector3){-p.dimension.x / 2.0f, p.position.y, -p.dimension.y / 2.0f};
  bb.max = (Vector3){p.dimension.x / 2.0f, p.position.y, p.dimension.y / 2.0f};
  return bb;
}

inline BoundingBox InitCubeBoundingBox(World::Cube c) {
  BoundingBox bb;
  bb.min = (Vector3){c.position.x - c.size.x / 2.0f, 0.0f,
                     c.position.z - c.size.z / 2.0f};
  bb.max = (Vector3){c.position.x + c.size.x / 2.0f, c.size.y,
                     c.position.z + c.size.z / 2.0f};
  return bb;
}
} // namespace Utility
