#include <systems/ZCollisionSystem.h>

void ZCollisionSystem::Update(Registry &registry) {
  auto &buffer = registry.getResource<CollisionBuffer>();

  for (const auto &info : buffer.collisions) {
    if (info.axis == CollisionInfo::Axis::Z) {
        std::cout << "locking z" << std::endl;
      LockZAxis(info, registry);
      auto &transform = registry.getComponent<TransformComponent>(info.entity1);
      auto &size = registry.getComponent<SizeComponent>(info.entity1);
      registry.getComponent<ColliderComponent>(info.entity1)
          .UpdateBounds(transform.position, size.size);
    }
  }
}
