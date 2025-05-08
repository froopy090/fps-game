#pragma once

#include <Component.h>
#include <Registry.h>
#include <iostream>
#include <shared/SharedResources.h>
#include <systems/System.h>

class ZCollisionSystem : public System {
public:
  void Update(Registry &registry) override;

private:
  float offset = 0.25f;
  void LockZAxis(CollisionInfo collision, Registry &registry) {
    auto &transform =
        registry.getComponent<TransformComponent>(collision.entity1);
    auto &velocity =
        registry.getComponent<VelocityComponent>(collision.entity1);
    auto &size = registry.getComponent<SizeComponent>(collision.entity1);

    if (collision.axis == CollisionInfo::Axis::Z) {
      std::cout << "found z axis collision" << std::endl;
      if (collision.direction == CollisionInfo::Direction::UP) {
        std::cout << "applying collision" << std::endl;
        transform.position.z = collision.box2.min.z - size.size.z + offset;
        velocity.velocity.z = 0.0f;
      }

      if (collision.direction == CollisionInfo::Direction::DOWN) {
        transform.position.z = collision.box2.max.z + size.size.z - offset;
        velocity.velocity.z = 0.0f;
      }
    }
  }
};
