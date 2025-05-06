#include <systems/YCollisionSystem.h>

void YCollisionSystem::Update(Registry &registry) {
  auto &buffer = registry.getResource<CollisionBuffer>();
  std::unordered_set<Entity> groundedEntities;

  for (const auto &info : buffer.collisions) {
    if (info.axis == CollisionInfo::Axis::Y &&
        info.direction == CollisionInfo::Direction::TOP) {
      // std::cout << "found a y axis collision" << std::endl;
      groundedEntities.insert(info.entity1);
      registry.getComponent<GroundedComponent>(info.entity1).isGrounded = true;

      auto &transform = registry.getComponent<TransformComponent>(info.entity1);
      // auto &velocity = registry.getComponent<VelocityComponent>(info.entity1);
      auto &size = registry.getComponent<SizeComponent>(info.entity1);

      LockYAxis(info, registry);
      registry.getComponent<ColliderComponent>(info.entity1)
          .UpdateBounds(transform.position, size.size);
    }

    if (info.axis == CollisionInfo::Axis::Y &&
        info.direction == CollisionInfo::Direction::BOTTOM) {
      auto &transform = registry.getComponent<TransformComponent>(info.entity1);
      auto &velocity = registry.getComponent<VelocityComponent>(info.entity1);
      auto &size = registry.getComponent<SizeComponent>(info.entity1);

      LockYAxis(info, registry);
      registry.getComponent<ColliderComponent>(info.entity1)
          .UpdateBounds(transform.position, size.size);
    }
  }

  for (Entity e : registry.view<GroundedComponent>()) {
    if (groundedEntities.count(e) == 0) {
      registry.getComponent<GroundedComponent>(e).isGrounded = false;
    }
  }
}
