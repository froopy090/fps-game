#include <entities/PlayerFactory.h>

Entity CreatePlayer(Registry &registry) {
  Entity player = registry.createEntity();

  registry.addComponent(player,
                        TransformComponent{.position = {0.0f, 20.0f, 4.0f}});
  registry.addComponent(player, VelocityComponent{.velocity = Vector3Zero()});
  registry.addComponent(
      player,
      ViewCameraComponent{.camera = Camera3D{.position = {0.0f, 20.0f, 4.0f},
                                             .target = {0.0f, 2.0f, 0.0f},
                                             .up = {0.0f, 1.0f, 0.0f},
                                             .fovy = 60.0f,
                                             .projection = CAMERA_PERSPECTIVE},
                          .cameraMode = CAMERA_FIRST_PERSON});
  registry.addComponent(player, ColliderComponent{});
  return player;
}
