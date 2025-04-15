#pragma once
#include "Entities/Player.h"
#include "Utility/EnemyManager.h"

namespace World {
class Room {
public:
  virtual void Update() = 0;
  virtual void Draw() = 0;

protected:
  // Helper functions
  void Reset(Entities::Player *player, Utility::EnemyManager *enemyManager) {
    player->SetPlaneCollision(false);
    for (auto &enemy : *enemyManager->GetEnemiesVector()) {
      enemy->SetPlaneCollision(false);
    }
  }
};
} // namespace World
