#include <systems/CollisionDetectionSystem.h>

void CollisionDetectionSystem::Update(Registry &registry) {
  auto entities = registry.view<TransformComponent, ColliderComponent>();
  auto &buffer = registry.getResource<CollisionBuffer>();
  buffer.collisions.clear();

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

      // Check if entity a is colliding on x axis with b
      CollisionInfo xCollision = XAxisCollision(a, b, registry);
      if (xCollision.collided) {
        std::cout << "x collision" << std::endl;
        buffer.collisions.push_back(xCollision);
      }

      // Check if entity a is colliding on z axis with b
      CollisionInfo zCollision = ZAxisCollision(a, b, registry);
      if (zCollision.collided) {
        std::cout << "z collision" << std::endl;
        buffer.collisions.push_back(zCollision);
      }

      // Check if moving entity a is colliding on the y axis with b
      CollisionInfo yCollision = YAxisCollision(a, b, registry);
      if (yCollision.collided) {
        std::cout << "y collision" << std::endl;
        buffer.collisions.push_back(yCollision);
      }
    }
  }
}
