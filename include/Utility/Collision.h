#pragma once
#include "raylib.h"
#include <iostream>

namespace Utility {
template <typename Shooter, typename Target>
inline bool HitscanIntersectsBox(const Shooter &shooter, const Target &target) {
  return shooter->IsShooting() &&
         GetRayCollisionBox(shooter->GetRay(), target->GetBoundingBox()).hit;
}

// checks to see if the entity can see the target
template <typename Entity, typename Target, typename Object>
inline bool CanSeeTarget(const Entity &entity, const Target &target,
                         const Object &object) {
  return !(
      GetRayCollisionBox(entity->GetRay(), object->GetBoundingBox()).hit &&
      GetRayCollisionBox(entity->GetRay(), object->GetBoundingBox()).distance <=
          Vector3Distance(target->GetPosition(), entity->GetPosition()));
}

template <typename Entity, typename Object>
inline bool EntityCollisionObject(const Entity &entity, const Object &object) {
  return CheckCollisionBoxes(entity->GetBoundingBox(),
                             object->GetBoundingBox());
}

template <typename Entity, typename Object>
inline bool XAxisCollision(const Entity &entity, const Object &IceCube) {
  // real ones know about playa, respect
  return entity->GetBoundingBox().min.x < IceCube->GetBoundingBox().min.x ||
         entity->GetBoundingBox().max.x > IceCube->GetBoundingBox().max.x;
}

template <typename Entity, typename Object>
inline bool YAxisCollision(const Entity &entity, const Object &IceCube) {
  return entity->GetBoundingBox().max.y >= IceCube->GetBoundingBox().max.y;
}

template <typename Entity, typename Object>
inline bool ZAxisCollision(const Entity &entity, const Object &IceCube) {
  return entity->GetBoundingBox().min.z < IceCube->GetBoundingBox().min.z ||
         entity->GetBoundingBox().max.z > IceCube->GetBoundingBox().max.z;
}

template <typename Entity> inline void LockXAxis(const Entity &entity) {
  entity->SetXPosition(entity->GetPreviousPosition().x);
}

template <typename Entity> inline void LockZAxis(const Entity &entity) {
  entity->SetZPosition(entity->GetPreviousPosition().z);
}

// this lock is specifically used when on top of a box
template <typename Entity, typename Object>
inline void LockYAxis(const Entity &entity, const Object &IceCube) {
  entity->SetYPosition(IceCube->GetBoundingBox().max.y + entity->GetSize().y);
  entity->SetPlaneCollision(true);
}

// this function uses the player's velocity to calculate HOW
// we collide with the cube, based on that, we lock the appropriate
// axis
// RIP playa variable name
template <typename Entity, typename Object>
inline void LockEntityAxis(const Entity &entity, const Object &IceCube) {
  // Y axis movement
  // if player is on top of box
  if (YAxisCollision(entity, IceCube)) {
    LockYAxis(entity, IceCube);
    return;
  }
  // XZ axis movement
  //  this is the exception, where player is in the corner
  //  if we have collision on BOTH axiis
  if (XAxisCollision(entity, IceCube) && ZAxisCollision(entity, IceCube)) {
    // case 1, xVel > 0, zVel < 0
    if (entity->GetVelocity().x > 0.0f && entity->GetVelocity().z < 0.0f) {
      std::cout << "Case 1" << std::endl;
      // bottom right corner
      if (entity->GetBoundingBox().min.x <= IceCube->GetBoundingBox().min.x &&
          entity->GetBoundingBox().min.z < IceCube->GetBoundingBox().min.z) {
        std::cout << "bottom right" << std::endl;
        LockXAxis(entity);
        return;
      }
      // top left corner
      if (entity->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          entity->GetBoundingBox().max.x > IceCube->GetBoundingBox().max.x) {
        std::cout << "top left" << std::endl;
        LockZAxis(entity);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (entity->GetBoundingBox().min.x + entity->GetSize().x >
              IceCube->GetBoundingBox().max.x - IceCube->GetSize().x + 0.1f &&
          entity->GetBoundingBox().min.z <
              IceCube->GetBoundingBox().max.z - 0.1f &&
          entity->GetBoundingBox().min.x + entity->GetSize().x <
              IceCube->GetBoundingBox().max.x - IceCube->GetSize().x + 0.5f &&
          entity->GetBoundingBox().min.z >
              IceCube->GetBoundingBox().max.z - 0.5f) {
        LockXAxis(entity);
        LockZAxis(entity);
        return;
      }
    }

    // case 2, xVel < 0, zVel > 0
    if (entity->GetVelocity().x < 0.0f && entity->GetVelocity().z > 0.0f) {
      std::cout << "Case 2" << std::endl;
      // bottom right corner
      if (entity->GetBoundingBox().min.x <= IceCube->GetBoundingBox().min.x &&
          entity->GetBoundingBox().min.z < IceCube->GetBoundingBox().min.z) {
        std::cout << "bottom right" << std::endl;
        LockZAxis(entity);
        return;
      }
      // top left corner
      if (entity->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          entity->GetBoundingBox().max.x > IceCube->GetBoundingBox().max.x) {
        std::cout << "top left" << std::endl;
        LockXAxis(entity);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (entity->GetBoundingBox().max.x - entity->GetSize().x <
              IceCube->GetBoundingBox().min.x + IceCube->GetSize().x - 0.1f &&
          entity->GetBoundingBox().max.z >
              IceCube->GetBoundingBox().min.z + 0.1f &&
          entity->GetBoundingBox().max.x - entity->GetSize().x >
              IceCube->GetBoundingBox().min.x + IceCube->GetSize().x - 0.5f &&
          entity->GetBoundingBox().max.z <
              IceCube->GetBoundingBox().min.z + 0.5f) {
        LockXAxis(entity);
        LockZAxis(entity);
        return;
      }
    }

    // case 3, xVel < 0, zVel < 0
    if (entity->GetVelocity().x < 0.0f && entity->GetVelocity().z < 0.0f) {
      std::cout << "Case 3" << std::endl;
      // top right corner
      if (entity->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          entity->GetBoundingBox().max.x < IceCube->GetBoundingBox().max.x &&
          entity->GetBoundingBox().max.x > IceCube->GetBoundingBox().min.x) {
        std::cout << "top right" << std::endl;
        LockZAxis(entity);
        return;
      }
      // bottom left corner
      if (entity->GetBoundingBox().max.x >= IceCube->GetBoundingBox().max.x &&
          entity->GetBoundingBox().max.z < IceCube->GetBoundingBox().max.z) {
        std::cout << "bottom left" << std::endl;
        LockXAxis(entity);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (entity->GetBoundingBox().min.x <
              IceCube->GetBoundingBox().max.x - 0.1f &&
          entity->GetBoundingBox().min.z <
              IceCube->GetBoundingBox().max.z - 0.1f &&
          entity->GetBoundingBox().min.x >
              IceCube->GetBoundingBox().max.x - 0.5f &&
          entity->GetBoundingBox().min.z >
              IceCube->GetBoundingBox().max.z - 0.5f) {
        LockXAxis(entity);
        LockZAxis(entity);
        return;
      }
    }

    // case 4, xVel > 0, zVel > 0
    if (entity->GetVelocity().x > 0.0f && entity->GetVelocity().z > 0.0f) {
      std::cout << "Case 4" << std::endl;
      // top right corner
      if (entity->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          entity->GetBoundingBox().max.x < IceCube->GetBoundingBox().max.x) {
        std::cout << "top right" << std::endl;
        LockXAxis(entity);
        return;
      }
      // bottom left corner
      if (entity->GetBoundingBox().max.x >= IceCube->GetBoundingBox().max.x &&
          entity->GetBoundingBox().max.z < IceCube->GetBoundingBox().max.z) {
        std::cout << "bottom left" << std::endl;
        LockZAxis(entity);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (entity->GetBoundingBox().max.x >
              IceCube->GetBoundingBox().min.x + 0.1f &&
          entity->GetBoundingBox().max.z >
              IceCube->GetBoundingBox().min.z + 0.1f &&
          entity->GetBoundingBox().max.x <
              IceCube->GetBoundingBox().min.x + 0.5f &&
          entity->GetBoundingBox().max.z <
              IceCube->GetBoundingBox().min.z + 0.5f) {
        LockXAxis(entity);
        LockZAxis(entity);
        return;
      }
    }
    // return; // dr carbon, absolute legend
  } else if (XAxisCollision(entity, IceCube)) {
    LockXAxis(entity);
  } else if (ZAxisCollision(entity, IceCube)) {
    LockZAxis(entity);
  } else {
    std::cout << "all collision checks failed" << std::endl;
  }
}
} // namespace Utility
