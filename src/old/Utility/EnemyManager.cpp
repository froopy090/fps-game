#include "Utility/EnemyManager.h"
#include "Entities/Enemy.h"
#include "Entities/EntityDefinitions.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "algorithm"

namespace Utility {
EnemyManager::EnemyManager(int numberOfEnemies, Entities::Player *player,
                           Entities::Pistol *pistol)
    : numberOfEnemies(numberOfEnemies), player(player), pistol(pistol) {}

void EnemyManager::Event() {
  for (std::unique_ptr<Entities::Enemy> &enemy : enemies) {
    enemy->Event();
  }
}

void EnemyManager::Update() {
  if (enemies.empty()) {
    Entities::Enemy::CleanupSprite();
  }
  this->DespawnEnemy();
  for (std::unique_ptr<Entities::Enemy> &enemy : enemies) {
    enemy->Update();
  }
}

void EnemyManager::Draw() {
  for (std::unique_ptr<Entities::Enemy> &enemy : enemies) {
    enemy->Draw();
  }
}

void EnemyManager::SpawnEnemy(Vector3 position) {
  if (enemies.size() < numberOfEnemies)
    enemies.emplace_back(
        std::make_unique<Entities::Enemy>(player, pistol, position));
}

std::vector<std::unique_ptr<Entities::Enemy>> *
EnemyManager::GetEnemiesVector() {
  return &enemies;
}

// Helper functions
// -------------------------------------------------------------
void EnemyManager::DespawnEnemy() {
  enemies.erase(
      std::remove_if(enemies.begin(), enemies.end(),
                     [](const std::unique_ptr<Entities::Enemy> &enemy) {
                       return enemy->GetState() == Entities::ENEMY_DEAD;
                     }),
      enemies.end());
};
// End Helper functions --------------------------------------------------------
} // namespace Utility
