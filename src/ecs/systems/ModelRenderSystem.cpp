#include <iostream>
#include <systems/ModelRenderSystem.h>
void ModelRenderSystem::Update(Registry &registry) {
  // auto &models = registry.getMap<ModelComponent>();
  auto &transforms = registry.getMap<TransformComponent>();
  auto &colliders = registry.getMap<ColliderComponent>();
  auto &objectTypes = registry.getMap<MapObjectTypeComponent>();

  // for (auto &[entity, model] : models) {
  //   if (transforms.contains(entity)) {
  //     const Vector3 &pos = transforms[entity].position;
  //     DrawModel(model.model, pos, 1.0f, WHITE);
  //   }
  // }

  std::vector<Entity> mapEntities =
      registry.view<ColliderComponent, MapObjectTypeComponent>();
  for (auto &entity : mapEntities) {
      std::cout<<"size: "<<mapEntities.size()<<std::endl;
    Vector3 &pos = transforms[entity].position;
    if (objectTypes[entity].id == 0) {
      DrawPlane(pos,
                (Vector2){colliders[entity].GetSize().x,
                          colliders[entity].GetSize().z},
                GRAY);
    }
    if (objectTypes[entity].id == 1) {
      DrawCubeV(pos, colliders[entity].GetSize(), GREEN);
    }
  }
}
