#pragma once
#include "raylib.h"
#include <iostream>

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
inline bool ZAxisCollision(const Entity &entity, const Object &IceCube) {
  return entity->GetBoundingBox().min.z < IceCube->GetBoundingBox().min.z ||
         entity->GetBoundingBox().max.z > IceCube->GetBoundingBox().max.z;
}

template <typename Entity> inline void LockXAxis(const Entity &player) {
  // TODO: generalize this for enemies as well
  player->camera.position.x = player->GetPreviousPosition().x;
}

template <typename Entity> inline void LockZAxis(const Entity &player) {
  // TODO: generalize for enemies too
  player->camera.position.z = player->GetPreviousPosition().z;
}

// this lock is specifically used when on top of a box
template <typename Entity, typename Object>
inline void LockYAxis(const Entity &player, const Object &IceCube) {
  player->camera.position.y =
      IceCube->GetBoundingBox().max.y + player->GetSize().y;
  player->SetPlaneCollision(true);
}

// this function uses the player's velocity to calculate HOW
// we collide with the cube, based on that, we lock the appropriate
// axis
template <typename Entity, typename Object>
inline void LockPlayerAxis(const Entity &playa, const Object &IceCube) {
  // Y axis movement
  // if player is on top of box
  if (playa->GetBoundingBox().max.y >= IceCube->GetBoundingBox().max.y) {
    LockYAxis(playa, IceCube);
    return;
  }
  // XZ axis movement
  //  this is the exception, where player is in the corner
  //  if we have collision on BOTH axiis
  if (XAxisCollision(playa, IceCube) && ZAxisCollision(playa, IceCube)) {
    // case 1, xVel > 0, zVel < 0
    if (playa->GetVelocity().x > 0.0f && playa->GetVelocity().z < 0.0f) {
      std::cout << "Case 1" << std::endl;
      // bottom right corner
      if (playa->GetBoundingBox().min.x <= IceCube->GetBoundingBox().min.x &&
          playa->GetBoundingBox().min.z < IceCube->GetBoundingBox().min.z) {
        std::cout << "bottom right" << std::endl;
        LockXAxis(playa);
        return;
      }
      // top left corner
      if (playa->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x > IceCube->GetBoundingBox().max.x) {
        std::cout << "top left" << std::endl;
        LockZAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().min.x + playa->GetSize().x >
              IceCube->GetBoundingBox().max.x - IceCube->GetSize().x + 0.1f &&
          playa->GetBoundingBox().min.z <
              IceCube->GetBoundingBox().max.z - 0.1f &&
          playa->GetBoundingBox().min.x + playa->GetSize().x <
              IceCube->GetBoundingBox().max.x - IceCube->GetSize().x + 0.5f &&
          playa->GetBoundingBox().min.z >
              IceCube->GetBoundingBox().max.z - 0.5f) {
        LockXAxis(playa);
        LockZAxis(playa);
      }
    }

    // case 2, xVel < 0, zVel > 0
    if (playa->GetVelocity().x < 0.0f && playa->GetVelocity().z > 0.0f) {
      std::cout << "Case 2" << std::endl;
      // bottom right corner
      if (playa->GetBoundingBox().min.x <= IceCube->GetBoundingBox().min.x &&
          playa->GetBoundingBox().min.z < IceCube->GetBoundingBox().min.z) {
        std::cout << "bottom right" << std::endl;
        LockZAxis(playa);
        return;
      }
      // top left corner
      if (playa->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x > IceCube->GetBoundingBox().max.x) {
        std::cout << "top left" << std::endl;
        LockXAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().max.x - playa->GetSize().x <
              IceCube->GetBoundingBox().min.x + IceCube->GetSize().x - 0.1f &&
          playa->GetBoundingBox().max.z >
              IceCube->GetBoundingBox().min.z + 0.1f &&
          playa->GetBoundingBox().max.x - playa->GetSize().x >
              IceCube->GetBoundingBox().min.x + IceCube->GetSize().x - 0.5f &&
          playa->GetBoundingBox().max.z <
              IceCube->GetBoundingBox().min.z + 0.5f) {
        LockXAxis(playa);
        LockZAxis(playa);
      }
    }

    // case 3, xVel < 0, zVel < 0
    if (playa->GetVelocity().x < 0.0f && playa->GetVelocity().z < 0.0f) {
      std::cout << "Case 3" << std::endl;
      // top right corner
      if (playa->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x < IceCube->GetBoundingBox().max.x &&
          playa->GetBoundingBox().max.x > IceCube->GetBoundingBox().min.x) {
        std::cout << "top right" << std::endl;
        LockZAxis(playa);
        return;
      }
      // bottom left corner
      if (playa->GetBoundingBox().max.x >= IceCube->GetBoundingBox().max.x &&
          playa->GetBoundingBox().max.z < IceCube->GetBoundingBox().max.z) {
        std::cout << "bottom left" << std::endl;
        LockXAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().min.x <
              IceCube->GetBoundingBox().max.x - 0.1f &&
          playa->GetBoundingBox().min.z <
              IceCube->GetBoundingBox().max.z - 0.1f &&
          playa->GetBoundingBox().min.x >
              IceCube->GetBoundingBox().max.x - 0.5f &&
          playa->GetBoundingBox().min.z >
              IceCube->GetBoundingBox().max.z - 0.5f) {
        LockXAxis(playa);
        LockZAxis(playa);
      }
    }

    // case 4, xVel > 0, zVel > 0
    if (playa->GetVelocity().x > 0.0f && playa->GetVelocity().z > 0.0f) {
      std::cout << "Case 4" << std::endl;
      // top right corner
      if (playa->GetBoundingBox().max.z >= IceCube->GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x < IceCube->GetBoundingBox().max.x) {
        std::cout << "top right" << std::endl;
        LockXAxis(playa);
        return;
      }
      // bottom left corner
      if (playa->GetBoundingBox().max.x >= IceCube->GetBoundingBox().max.x &&
          playa->GetBoundingBox().max.z < IceCube->GetBoundingBox().max.z) {
        std::cout << "bottom left" << std::endl;
        LockZAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().max.x >
              IceCube->GetBoundingBox().min.x + 0.1f &&
          playa->GetBoundingBox().max.z >
              IceCube->GetBoundingBox().min.z + 0.1f &&
          playa->GetBoundingBox().max.x <
              IceCube->GetBoundingBox().min.x + 0.5f &&
          playa->GetBoundingBox().max.z <
              IceCube->GetBoundingBox().min.z + 0.5f) {
        LockXAxis(playa);
        LockZAxis(playa);
      }
    }
    // return; // dr carbon, absolute legend
  } else if (XAxisCollision(playa, IceCube)) {
    LockXAxis(playa);
  } else if (ZAxisCollision(playa, IceCube)) {
    LockZAxis(playa);
  } else {
    std::cout << "all collision checks failed" << std::endl;
  }
}
} // namespace Utility
