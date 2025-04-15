#include "Entities/Pistol.h"
#include "Entities/EntityDefinitions.h"
#include "Entities/Player.h"
#include "globals.h"
#include "iostream"

namespace Entities {
Pistol::Pistol(Player *player) : player(player) {
  // Loading texture
  texture = LoadTexture("DOOM_Pistol_Cropped.png");

  state = WEAPON_IDLE;
  // Idle sprite
  idle.source = (Rectangle){10, 50, 110, 95};
  idle.destination = (Rectangle){200, screenHeight - 95 * 3, 110 * 3, 95 * 3};
  idle.origin = (Vector2){0.0f, 0.0f};
  idle.rotation = 0.0f;
  idle.tint = WHITE;

  // Firing1 sprite
  firing1.source = (Rectangle){125, 30, 120, 115};
  firing1.destination =
      (Rectangle){200, screenHeight - 115 * 3, 120 * 3, 115 * 3};
  firing1.origin = (Vector2){0.0f, 0.0f};
  firing1.rotation = 0.0f;
  firing1.tint = WHITE;

  // Firing2 sprite
  firing2.source = (Rectangle){383, 300, 42, 38};
  firing2.destination = (Rectangle){
      200 + 79 * 3 - 5 * 3, screenHeight - 115 * 3 - 21 * 3, 42 * 3, 38 * 3};
  firing2.origin = (Vector2){0.0f, 0.0f};
  firing2.rotation = 0.0f;
  firing2.tint = WHITE;

  // Damage init
  damage = 30.0f;
}

Pistol::~Pistol() { UnloadTexture(texture); }

void Pistol::Event() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    state = WEAPON_FIRING;
    timer.Start(0.2f);
  }
}

void Pistol::Update() {
  timer.Update();
  if (timer.Finished()) {
    state = WEAPON_IDLE;
  }
}

void Pistol::Draw() {
  if (player->cameraMode == CAMERA_FIRST_PERSON) {
    switch (state) {
    case WEAPON_IDLE:
      DrawTexturePro(texture, idle.source, idle.destination, idle.origin,
                     idle.rotation, idle.tint);
      break;
    case WEAPON_FIRING:
      DrawTexturePro(texture, firing1.source, firing1.destination,
                     firing1.origin, firing1.rotation, firing1.tint);
      DrawTexturePro(texture, firing2.source, firing2.destination,
                     firing2.origin, firing2.rotation, firing2.tint);
      break;
    case WEAPON_RELOADING:
      // TODO: add draw texture function
      break;
    default:
      break;
    }
  }
}

float Pistol::GetDamage() { return damage; }
} // namespace Entities
