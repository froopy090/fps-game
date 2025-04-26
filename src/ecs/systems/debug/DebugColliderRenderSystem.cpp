#include <systems/debug/DebugColliderRenderSystem.h>

void DebugColliderRenderSystem::Update(Registry &registry) {
  auto &colliders = registry.getMap<ColliderComponent>();

  for (auto &[entity, collider] : colliders) {
    DrawBoundingBox(collider.bounds, RED);
  }
}
