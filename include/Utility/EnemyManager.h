#pragma once
#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "vector"

namespace Utility {
class EnemyManager {
public:
  EnemyManager(int numberOfEnemies, Entities::Player *player, Entities::Pistol *pistol);

  void Event();
  void Update();
  void Draw();

  // adds an enemy to the vector
  void SpawnEnemy(Vector3 position);

  std::vector<Entities::Enemy> *GetEnemiesVector();

private:
  std::vector<Entities::Enemy> enemies;
  int numberOfEnemies;
  Entities::Player *player;
  Entities::Pistol *pistol;
};
} // namespace Utility
