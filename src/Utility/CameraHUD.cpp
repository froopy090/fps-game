#include "Utility/CameraHUD.h"
#include "globals.h"
#include "raylib.h"

namespace Utility {
void CameraHUD::Draw(Entities::Player *player) {
  // Camera Info
  DrawRectangle(700, 5, 350, 170, Fade(SKYBLUE, 0.5f));
  DrawRectangleLines(700, 5, 350, 170, BLUE);

  DrawText("Camera Status:", 710, 15, 15, BLACK);

  DrawText(TextFormat("- Mode: %s", (player->cameraMode == CAMERA_FIRST_PERSON
                                         ? "FIRST PERSON"
                                         : "FUCK MY ASS")),
           710, 40, 15, BLACK);
  DrawText(TextFormat("- Projection: %s",
                      (player->camera.projection == CAMERA_PERSPECTIVE
                           ? "PERSPECTIVE"
                           : "FUCK MY ASS AGAIN")),
           710, 65, 15, BLACK);
  DrawText(TextFormat("- Position: (%06.3f, %06.3f, %03.6f)",
                      player->camera.position.x, player->camera.position.y,
                      player->camera.position.z),
           710, 90, 15, BLACK);
  DrawText(TextFormat("- Target: (%06.3f, %06.3f, %03.6f)",
                      player->camera.target.x, player->camera.target.y,
                      player->camera.target.z),
           710, 115, 15, BLACK);
  DrawText(TextFormat("- Up: (%06.3f, %06.3f, %03.6f)", player->camera.up.x,
                      player->camera.up.y, player->camera.up.z),
           710, 140, 15, BLACK);
  

  // Crosshair
  DrawLineV((Vector2){screenWidth / 2.0f, screenHeight / 2.0f - 5},
            (Vector2){screenWidth / 2.0f, screenHeight / 2.0f + 5}, PURPLE);
  DrawLineV((Vector2){screenWidth / 2.0f - 5, screenHeight / 2.0f},
            (Vector2){screenWidth / 2.0f + 5, screenHeight / 2.0f}, PURPLE);
}
} // namespace Utility
