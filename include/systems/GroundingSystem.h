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
  void LockYAxis(CollisionInfo collision, Registry &registry) {
    auto &transform =
        registry.getComponent<TransformComponent>(collision.entity1);
    auto &velocity =
        registry.getComponent<VelocityComponent>(collision.entity1);
    auto &size = registry.getComponent<SizeComponent>(collision.entity1);

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
