#pragma once

#include <Component.h>
#include <Registry.h>
#include <iostream>
#include <shared/SharedResources.h>
#include <systems/System.h>
#include <unordered_set>

class GroundingSystem : public System {
public:
  void Update(Registry &registry) override;

private:
  void LockYAxis(TransformComponent &transform, VelocityComponent &velocity,
                 SizeComponent &size, CollisionInfo collision) {
    if (collision.direction == CollisionInfo::Direction::TOP) {
      transform.position.y = collision.box2.max.y + size.size.y;
      velocity.velocity.y = 0.0f;
      std::cout << "locking y axis TOP" << std::endl;
    }

    if (collision.direction == CollisionInfo::Direction::BOTTOM) {
      transform.position.y = collision.box2.min.y - size.size.y;
      velocity.velocity.y = 0.0f;
      std::cout << "locking y axis BOTTOM" << std::endl;
    }
  }
};
