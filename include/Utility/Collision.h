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

template <typename Player, typename Object>
inline bool xAxisCollision(Player playa, Object &IceCube) {
  return playa->GetBoundingBox().min.x < IceCube.GetBoundingBox().min.x ||
          playa->GetBoundingBox().max.x > IceCube.GetBoundingBox().max.x;
}

template <typename Player, typename Object>
inline bool zAxisCollision(Player playa, Object &IceCube) {
  return playa->GetBoundingBox().min.z < IceCube.GetBoundingBox().min.z ||
          playa->GetBoundingBox().max.z > IceCube.GetBoundingBox().max.z;
}

template <typename Player, typename Object>
inline bool yAxisCollision(Player playa, Object &IceCube) {
  return playa->GetBoundingBox().min.y < IceCube.GetBoundingBox().max.y &&
        playa->GetBoundingBox().max.y > IceCube.GetBoundingBox().max.y;
}

template <typename Player, typename Object>
inline void lockAxis(Player playa, Object &IceCube) {
  // check to see if cube is ahead of playa in x axis
  if (Utility::xAxisCollision(playa, IceCube)) {
    playa->camera.position.x = playa->GetPreviousPosition().x;
  }
  if (Utility::zAxisCollision(playa, IceCube)) {
    playa->camera.position.z = playa->GetPreviousPosition().z;
  }
}

template <typename Player, typename Object>
inline void collide(Player playa, Object worldObject) {
  if (Utility::EntityCollisionObject(playa, &worldObject)) {
    // if player's bottom half is inside worldObject
    if (yAxisCollision(playa, worldObject)) {
      playa->camera.position.y =
          worldObject.GetBoundingBox().max.y + playa->GetSize().y;
    } else { // else prevent them from phasing into worldObject
      lockAxis(playa, worldObject);
    }
    playa->SetPlaneCollision(true);
  }
}

} // namespace Utility
