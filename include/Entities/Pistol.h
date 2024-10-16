#pragma once
#include "raylib.h"
#include "Utility/Timer.h"
#include "Entities/Player.h"


namespace Entities {
struct Sprite{
  Rectangle source;
  Rectangle destination;
  Vector2 origin;
  float rotation;
  Color tint;
} ;

typedef enum State{IDLE, FIRING, RELOADING} State;

class Pistol {
public:
  Pistol();
  ~Pistol();
  void Event();
  void Update();
  void Draw(Player *player);

private:
  Texture2D texture;
  State state;
  Utility::Timer timer;
  Sprite idle;
  Sprite firing1;
  Sprite firing2;
};
} // namespace Entities
