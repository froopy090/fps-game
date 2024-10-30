#pragma once
#include "raylib.h"

namespace Utility {
template <typename Shooter, typename Target>
inline bool HitscanIntersectsBox(const Shooter &shooter, const Target &target) {
  if (shooter->IsShooting() &&
      GetRayCollisionBox(shooter->GetRay(), target->GetBoundingBox()).hit) {
    return true;
  } else {
    return false;
  }
}

template <typename Entity, typename Object>
inline bool EntityCollisionObject(const Entity &entity, const Object &object) {
  return CheckCollisionBoxes(entity->GetBoundingBox(), object->GetBoundingBox());
}
} // namespace Utility
