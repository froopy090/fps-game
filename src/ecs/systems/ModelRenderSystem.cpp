#include <ecs/ModelRenderSystem.h>

void ModelRenderSystem::Update(Registry &registry) {
  auto &models = registry.getMap<ModelComponent>();

  for (auto &[entity, model] : models) {
    DrawModel(model.model, model.position, 1.0f, WHITE);
  }
}
