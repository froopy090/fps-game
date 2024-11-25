#include "Utility/EnemyManager.h"
#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"

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

  for (std::unique_ptr<Entities::Enemy> &enemy : enemies) {
    enemy->Update(player, pistol);
  }
}

void EnemyManager::Draw() {
  for (std::unique_ptr<Entities::Enemy> &enemy : enemies) {
    enemy->Draw(player);
  }
}

void EnemyManager::SpawnEnemy(Vector3 position) {
  if (enemies.size() < numberOfEnemies)
    enemies.emplace_back(std::make_unique<Entities::Enemy>(player, position));
}

std::vector<std::unique_ptr<Entities::Enemy>> *
EnemyManager::GetEnemiesVector() {
  return &enemies;
}
} // namespace Utility
