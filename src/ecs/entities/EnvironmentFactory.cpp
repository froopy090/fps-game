#include <entities/EnvironmentFactory.h>
#include <iostream>
#define TILE_SIZE 5
#define WALL_HEIGHT 3
#define MAP_SIZE 5

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

Entity CreatePlanePosition(Registry &registry, Vector3 position) {
  Entity plane = registry.createEntity();

  Model model = LoadModel("simple_plane.obj");
  Texture2D texture = LoadTexture("concrete.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

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

  Vector3 position = {0.0f, 6.0f, 0.0f};
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

Entity CreateCubePosition(Registry &registry, Vector3 position) {
  Entity cube = registry.createEntity();

  Model model = LoadModel("cube.obj");
  Texture2D texture = LoadTexture("concrete.png");
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

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

void CreateMap(Registry &registry) {
  const int mapMatrix[MAP_SIZE][MAP_SIZE] = {{1, 1, 1, 1, 1},
                                             {1, 0, 0, 0, 1},
                                             {1, 1, 0, 0, 1},
                                             {1, 0, 0, 0, 1},
                                             {1, 1, 1, 1, 1}};
  int center = MAP_SIZE / 2;
  for (uint i = 0; i < MAP_SIZE; i++) {
    for (uint j = 0; j < MAP_SIZE; j++) {
      std::cout << "creating map object" << std::endl;
      Entity mapElement = registry.createEntity();

      TransformComponent t;
      float x = (i - center) * (-TILE_SIZE);
      float y;
      if (mapMatrix[i][j] == 0) { // plane
        y = 0.0f;
      }
      if (mapMatrix[i][j] == 1) { // wall
        y = WALL_HEIGHT / 2.0f;
      }
      float z = (j - center) * (-TILE_SIZE);
      t.position = (Vector3){x, y, z};

      ColliderComponent c;
      c.isStatic = true;
      c.bounds.min = (Vector3){t.position.x - TILE_SIZE / 2.0f, 0.0f,
                               t.position.z - TILE_SIZE / 2.0f};
      if (mapMatrix[i][j] == 0) {
        c.bounds.max = (Vector3){t.position.x + TILE_SIZE / 2.0f, 0.0f,
                                 t.position.z + TILE_SIZE / 2.0f};
      } else {
        c.bounds.max = (Vector3){t.position.x + TILE_SIZE / 2.0f, WALL_HEIGHT,
                                 t.position.z + TILE_SIZE / 2.0f};
      }

      MapObjectTypeComponent m;
      m.id = mapMatrix[i][j];

      registry.addComponent(mapElement, c);
      registry.addComponent(mapElement, t);
      registry.addComponent(mapElement, m);
    }
  }
}
