#pragma once
#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "World/Room001.h"
#include "vector"

namespace Utility {
class EnemyManager {
public:
  EnemyManager(int numberOfEnemies, Entities::Player *player,
               Entities::Pistol *pistol, World::Room001 *room);

  void Event();
  void Update();
  void Draw();

private:
  std::vector<Entities::Enemy> enemies;
  int numberOfEnemies;
  Entities::Player *player;
  Entities::Pistol *pistol;
};
} // namespace Utility
