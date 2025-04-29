#include <iostream>
#include <systems/CollisionSystem.h>

void CollisionSystem::Update(Registry &registry) {
  auto entities = registry.view<TransformComponent, ColliderComponent>();

  for (Entity a : entities) {
    auto &aColliderComponent = registry.getComponent<ColliderComponent>(a);

    if (aColliderComponent.isStatic)
      continue; // only check dynamic entities (aka moving entities)

    auto &aTransformComponent = registry.getComponent<TransformComponent>(a);
    auto &aVelocityComponent = registry.getComponent<VelocityComponent>(a);
    auto &aSizeComponent = registry.getComponent<SizeComponent>(a);
    auto &aGroundedComponent = registry.getComponent<GroundedComponent>(a);

    for (Entity b : entities) {
      if (a == b)
        continue;

      auto &bColliderComponent = registry.getComponent<ColliderComponent>(b);
      auto &bTransformComponent = registry.getComponent<TransformComponent>(b);

      // First, update the bounding boxes of a
      // this catches anything that happened before collisions
      aColliderComponent.UpdateBounds(aTransformComponent.position,
                                      aSizeComponent.size);

      // Check if moving entity (a) is colliding on the y axis with b
      CollisionInfo yCollision =
          YAxisCollision(aColliderComponent.bounds, bColliderComponent.bounds);
      LockYAxis(aTransformComponent, aVelocityComponent, aSizeComponent,
                aGroundedComponent, yCollision);

      // Update with new position if collisions changed something
      aColliderComponent.UpdateBounds(aTransformComponent.position,
                                      aSizeComponent.size);
    }
  }
}
