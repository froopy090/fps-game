#pragma once
#include "raylib.h"
#include "Utility/Timer.h"
#include "Entities/EntityDefinitions.h"
#include "Entities/Player.h"


namespace Entities {
class Pistol {
public:
  Pistol();
  ~Pistol();
  void Event();
  void Update();
  void Draw(Player *player);
  float GetDamage();

private:
  Texture2D texture;
  State state;
  Utility::Timer timer;
  Sprite idle;
  Sprite firing1;
  Sprite firing2;
  float damage;
};
} // namespace Entities
