#include "Utility/PlayerInfoHUD.h"
#include "Entities/Player.h"
#include "raylib.h"

namespace Utility {
void PlayerInfoHUD::Draw(Entities::Player *player) {
  DrawRectangle(100, 5, 350, 170, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(100, 5, 350, 170, BLUE);

  DrawText("Player Info:", 110, 15, 14, BLACK);
  DrawText(TextFormat("-Health: (%06.3f)", player->GetHealth()), 110, 35, 14, BLACK);
  DrawText(TextFormat("- P.Position: (%06.3f, %06.3f, %03.6f)",
                      player->GetPosition().x, player->GetPosition().y,
                      player->GetPosition().z),
           110, 55, 14, BLACK);
}
} // namespace Utility
