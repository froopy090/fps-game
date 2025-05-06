#pragma once

#include <Component.h>
#include <Registry.h>
#include <shared/SharedResources.h>
#include <systems/System.h>

class XCollisionSystem : public System {
public:
  void Update(Registry &registry) override;

private:
  void LockXAxis(CollisionInfo collision, Registry &registry) {
    auto &transform =
        registry.getComponent<TransformComponent>(collision.entity1);
    auto &velocity =
        registry.getComponent<VelocityComponent>(collision.entity1);
    auto &size = registry.getComponent<SizeComponent>(collision.entity1);

    if (collision.axis == CollisionInfo::Axis::X) {
      if (collision.direction == CollisionInfo::Direction::LEFT) {
        transform.position.x = collision.box2.min.x + size.size.x;
        velocity.velocity.x = 0.0f;
      }

      if (collision.direction == CollisionInfo::Direction::RIGHT) {
        // float offset = 0.9f;
        transform.position.x = collision.box2.max.x - size.size.x;
        velocity.velocity.x = 0.0f;
      }
    }
  }
};
