#include <systems/PhysicsSystem.h>

void PhysicsSystem::Update(Registry &registry) {
  for (auto &[entity, vel] : registry.getMap<VelocityComponent>()) {
    if (!registry.hasComponent<TransformComponent>(entity) ||
        registry.getComponent<ColliderComponent>(entity).isStatic)
      continue;

    auto &transform = registry.getComponent<TransformComponent>(entity);

    // Apply gravity
    if (registry.hasComponent<GroundedComponent>(entity) &&
        !registry.getComponent<GroundedComponent>(entity).isGrounded) {
      vel.velocity.y += -9.8f * GetFrameTime();
    }

    // Apply movement
    transform.position = Vector3Add(transform.position,
                                    Vector3Scale(vel.velocity, GetFrameTime()));
  }
}
