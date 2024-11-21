#include "Utility/EnemyManager.h"
#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "World/Room001.h"
#include "World/WorldDefinitions.h"

namespace Utility {
EnemyManager::EnemyManager(int numberOfEnemies, Entities::Player *player,
                           Entities::Pistol *pistol, World::Room001 *room) {
  this->numberOfEnemies = numberOfEnemies;
  this->player = player;
  this->pistol = pistol;

  // Calculate center of matrix
  int center = World::ROOM_SIZE / 2;

  float randomValue = 0.0f;

  // Populate tiles with enemies (randomly)
  for (int i = 0; i < World::ROOM_SIZE; i++) {
    for (int j = 0; j < World::ROOM_SIZE; j++) {
      // calulating position of tile
      float x = (i - center) * (-World::TILE_SIZE);
      float z = (j - center) * (-World::TILE_SIZE);
      Vector3 position = {x, 0.0f, z};

      // generating a random value
      randomValue = GetRandomValue(0, 1);

      // spawning enemies
      if (room->GetRoomMatrix()[i][j] == 0) {
        if (randomValue <= 0.5f) {
          enemies.emplace_back(player, position);
        }
      } else if (room->GetRoomMatrix()[i][j] == 1) {
        if (randomValue <= 0.5f) {
          position.y = World::WALL_HEIGHT;
          enemies.emplace_back(player, position);
        }
      }
    }
  }
}

void EnemyManager::Event() {
  for (Entities::Enemy &enemy : enemies) {
    enemy.Event();
  }
}

void EnemyManager::Update() {

  for (Entities::Enemy &enemy : enemies) {
    enemy.Update(player, pistol);
  }
}

void EnemyManager::Draw() {
  for (Entities::Enemy &enemy : enemies) {
    enemy.Draw(player);
  }
}
} // namespace Utility
