#include <systems/ModelRenderSystem.h>

void ModelRenderSystem::Update(Registry &registry) {
  auto &models = registry.getMap<ModelComponent>();
  auto &transforms = registry.getMap<TransformComponent>();

  for (auto &[entity, model] : models) {
    if (transforms.contains(entity)) {
      const Vector3 &pos = transforms[entity].position;
      DrawModel(model.model, pos, 1.0f, WHITE);
      DrawBoundingBox(registry.getComponent<ColliderComponent>(entity).bounds, RED);
    }
  }
}
