#include <entities/PlayerFactory.h>

Entity CreatePlayer(Registry &registry) {
  Entity player = registry.createEntity();

  Vector3 playerPosition = (Vector3){0.0f, 20.0f, 4.0f};
  registry.addComponent(player, TransformComponent{.position = playerPosition});

  registry.addComponent(player, VelocityComponent{.velocity = Vector3Zero()});

  registry.addComponent(
      player,
      ViewCameraComponent{.camera = Camera3D{.position = playerPosition,
                                             .target = {0.0f, 2.0f, 0.0f},
                                             .up = {0.0f, 1.0f, 0.0f},
                                             .fovy = 60.0f,
                                             .projection = CAMERA_PERSPECTIVE},
                          .cameraMode = CAMERA_FIRST_PERSON});

  Vector3 playerSize = (Vector3){0.5f, 1.0f, 0.5f};
  registry.addComponent(player, SizeComponent{.size = playerSize});

  ColliderComponent collider;
  collider.bounds.min = (Vector3){playerPosition.x - playerSize.x / 2.0f,
                                  playerPosition.y - playerSize.y,
                                  playerPosition.z - playerSize.z / 2.0f};
  collider.bounds.max =
      (Vector3){playerPosition.x + playerSize.x / 2.0f, playerPosition.y,
                playerPosition.z + playerSize.z / 2.0f};
  collider.isStatic = false;
  registry.addComponent(player, collider);
  registry.addComponent(player, GroundedComponent{.isGrounded = false});
  return player;
}
