#include <systems/UpdateColliderSystem.h>

void UpdateColliderSystem::Update(Registry &registry) {
  std::vector<Entity> entities =
      registry.view<ColliderComponent, TransformComponent, SizeComponent>();

  for (Entity entity : entities) {
    auto &size = registry.getComponent<SizeComponent>(entity);
    auto &transform = registry.getComponent<TransformComponent>(entity);
    auto &collider = registry.getComponent<ColliderComponent>(entity);

    collider.bounds.min = (Vector3){transform.position.x - size.size.x / 2.0f,
                                    transform.position.y - size.size.y,
                                    transform.position.z - size.size.z / 2.0f};
    collider.bounds.max = (Vector3){transform.position.x + size.size.x / 2.0f,
                                    transform.position.y,
                                    transform.position.z + size.size.z / 2.0f};
  }
}
