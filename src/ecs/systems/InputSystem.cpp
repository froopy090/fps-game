#include <systems/InputSystem.h>
#include <iostream>

void InputSystem::Update(Registry &registry) {
  auto &velocities = registry.getMap<VelocityComponent>();
  auto &cameras = registry.getMap<ViewCameraComponent>();

  for (auto &[entity, velocity] : velocities) {
    // Only update if entity has a ViewCameraComponent
    if (!registry.hasComponent<ViewCameraComponent>(entity))
      continue;

    auto &camera = registry.getComponent<ViewCameraComponent>(entity).camera;

    // Reset X and Z velocity each frame
    velocity.velocity.x = 0.0f;
    velocity.velocity.z = 0.0f;

    const float moveSpeed = 5.0f;
    const float jumpForce = 10.0f;

    // Calculate the forward direction (XZ plane only)
    Vector3 forward =
        Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    forward.y = 0.0f;
    forward = Vector3Normalize(forward); // re-normalize after zeroing Y

    // Calculate right direction (perpendicular to forward)
    Vector3 right = {forward.z, 0.0f, -forward.x};

    // Input
    if (IsKeyDown(KEY_W)) {
      velocity.velocity.x += forward.x * moveSpeed;
      velocity.velocity.z += forward.z * moveSpeed;
    }
    if (IsKeyDown(KEY_S)) {
      velocity.velocity.x -= forward.x * moveSpeed;
      velocity.velocity.z -= forward.z * moveSpeed;
    }
    if (IsKeyDown(KEY_D)) {
      velocity.velocity.x -= right.x * moveSpeed;
      velocity.velocity.z -= right.z * moveSpeed;
    }
    if (IsKeyDown(KEY_A)) {
      velocity.velocity.x += right.x * moveSpeed;
      velocity.velocity.z += right.z * moveSpeed;
    }
    if (IsKeyPressed(KEY_SPACE)) {
      auto &grounded = registry.getComponent<GroundedComponent>(entity);
      if (grounded.isGrounded) {
        velocity.velocity.y = jumpForce;
        std::cout << "JUMPING" << std::endl;
      }
      else{
        std::cout << "apparently not grounded" << std::endl;
      }
    }
  }
}
