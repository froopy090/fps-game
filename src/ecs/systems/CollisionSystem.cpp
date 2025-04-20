#include <systems/CollisionSystem.h>
#include <iostream>

void CollisionSystem::Update(Registry &registry) {
  // auto entities = registry.view<TransformComponent, ColliderComponent>();
  //
  // for (Entity a : entities) {
  //   auto &aColliderComponent = registry.getComponent<ColliderComponent>(a);
  //   if (aColliderComponent.isStatic)
  //     continue; // only check dynamic entities (aka moving entities)
  //
  //   auto &aTransformComponent = registry.getComponent<TransformComponent>(a);
  //
  //   for (Entity b : entities) {
  //     if (a == b)
  //       continue;
  //
  //     auto &bColliderComponent = registry.getComponent<ColliderComponent>(b);
  //     auto &bTransformComponent = registry.getComponent<TransformComponent>(b);
  //
  //     // Check if moving entity (a) is colliding on the y axis with b
  //     if (CheckCollisionBoxes(aColliderComponent.bounds,
  //                             bColliderComponent.bounds)) {
  //       std::cout << "COLLISION BABYYY" << std::endl;
  //       aTransformComponent.position.y = bColliderComponent.bounds.max.y;
  //       registry.getComponent<VelocityComponent>(a).velocity.y = 0.0f;
  //     }
  //   }
  // }
}
