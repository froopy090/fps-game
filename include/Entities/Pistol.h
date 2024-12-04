#pragma once
#include "Entities/EntityDefinitions.h"
#include "Entities/Player.h"
#include "GameObject.h"
#include "Utility/Timer.h"
#include "raylib.h"

namespace Entities {
class Pistol : public GameObject {
public:
  Pistol(Player *player);
  ~Pistol();
  void Event() override;
  void Update() override;
  void Draw() override;
  float GetDamage();

private:
  Texture2D texture;
  WeaponState state;
  Utility::Timer timer;
  Sprite idle;
  Sprite firing1;
  Sprite firing2;
  float damage;
  Player *player;
};
} // namespace Entities
