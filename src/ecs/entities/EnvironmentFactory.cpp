#include <entities/EnvironmentFactory.h>

Entity CreatePlane(Registry &registry) {
  Entity plane = registry.createEntity();

  Model model = LoadModel("simple_plane.obj");
  Texture2D texture = LoadTexture("concrete.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

  Vector3 position = {0.0f, 0.0f, 0.0f};
  BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);
  bounds.max = Vector3Add(position, bounds.max);
  bounds.min = Vector3Add(position, bounds.min);

  ModelComponent modelComponent;
  modelComponent.model = model;
  modelComponent.texture = texture;

  registry.addComponent(plane, modelComponent);
  registry.addComponent(plane, TransformComponent{.position = position});
  registry.addComponent(plane,
                        ColliderComponent{.bounds = bounds, .isStatic = true});
  return plane;
}

Entity CreateCube(Registry &registry) {
  Entity cube = registry.createEntity();

  Model model = LoadModel("cube.obj");
  Texture2D texture = LoadTexture("concrete.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

  Vector3 position = {0.0f, 3.0f, 0.0f};
  BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);
  bounds.max = Vector3Add(position, bounds.max);
  bounds.min = Vector3Add(position, bounds.min);

  ModelComponent modelComponent;
  modelComponent.model = model;
  modelComponent.texture = texture;

  registry.addComponent(cube, modelComponent);
  registry.addComponent(cube, TransformComponent{.position = position});
  registry.addComponent(cube,
                        ColliderComponent{.bounds = bounds, .isStatic = true});
  return cube;
}
