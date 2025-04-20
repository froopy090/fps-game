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

  Camera3D camera = registry.getComponent<ViewCameraComponent>(player).camera;
  ColliderComponent collider;
  collider.bounds.min =
      (Vector3){camera.position.x - 0.25f, camera.position.y - 1.0f,
                camera.position.z - 0.25f};
  collider.bounds.max = (Vector3){camera.position.x + 0.25f, camera.position.y,
                                  camera.position.z + 0.25f};
  registry.addComponent(player, collider);
  return player;
}
