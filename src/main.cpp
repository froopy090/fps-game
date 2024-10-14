#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "globals.h"
#include "raylib.h"
#include "raymath.h"
#include <dirent.h>
#include <memory>
#include "World/TestMap.h"

#define MAX_COLUMNS 20

// Types and Structures Definition
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } Gamescreen;

int main() {
  // Initialization
  // ---------------------------------------------------------
  const int fps = 60;

  InitWindow(screenWidth, screenHeight, "fps");
  SetTargetFPS(fps);

  int framesCounter = 0;

  GameScreen currentScreen = LOGO;
      
  // World
  auto testMap = std::make_unique<World::TestMap>();

  // Loading Entities
  auto pistol = std::make_unique<Entities::Pistol>();
  auto player1 = std::make_unique<Entities::Player>();

  //--------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) {
    // Events
    // --------------------------------------------------------
    pistol->Event();

    // --------------------------------------------------------
    // Update
    // --------------------------------------------------------
    switch (currentScreen) {
    case LOGO:
      framesCounter++;

      // waiting for 4 seconds
      if (framesCounter > fps * 4) {
        currentScreen = TITLE;
      }
      break;
    case TITLE:
      if (IsKeyPressed(KEY_ENTER)) {
        currentScreen = GAMEPLAY;
      }
      break;
    case GAMEPLAY:
      // TODO: update game screen variables here
      pistol->Update();
      player1->Update();

      // UpdateCamera(&camera, cameraMode);

      break;
    case ENDING:
      // TODO: update ending variables here
      break;
    default:
      break;
    }
    //--------------------------------------------------------

    // Draw
    // -------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentScreen) {
    case LOGO:
      DrawText("Froopy Games", 20, 20, 40, LIGHTGRAY);
      break;
    case TITLE:
      DrawText("Epic Title", 20, 20, 40, LIGHTGRAY);
      DrawText("Press ENTER to continue", 20, 200, 40, LIGHTGRAY);
      break;
    case GAMEPLAY:
      // TODO: update game screen variables here

      testMap->Draw(player1.get());
      player1->Draw();
      pistol->Draw();

      // Debug Stuff
      DrawRectangle(700, 5, 350, 170, Fade(SKYBLUE, 0.5f));
      DrawRectangleLines(700, 5, 350, 170, BLUE);

      DrawText("Camera Status:", 710, 15, 15, BLACK);

      DrawText(
          TextFormat("- Mode: %s", (player1->cameraMode == CAMERA_FIRST_PERSON
                                        ? "FIRST PERSON"
                                        : "FUCK MY ASS")),
          710, 40, 15, BLACK);
      DrawText(TextFormat("- Projection: %s",
                          (player1->camera.projection == CAMERA_PERSPECTIVE
                               ? "PERSPECTIVE"
                               : "FUCK MY ASS AGAIN")),
               710, 65, 15, BLACK);
      DrawText(TextFormat("- Position: (%06.3f, %06.3f, %03.6f)",
                          player1->camera.position.x,
                          player1->camera.position.y,
                          player1->camera.position.z),
               710, 90, 15, BLACK);
      DrawText(TextFormat("- Target: (%06.3f, %06.3f, %03.6f)",
                          player1->camera.target.x, player1->camera.target.y,
                          player1->camera.target.z),
               710, 115, 15, BLACK);
      DrawText(TextFormat("- Up: (%06.3f, %06.3f, %03.6f)",
                          player1->camera.up.x, player1->camera.up.y,
                          player1->camera.up.z),
               710, 140, 15, BLACK);

      DrawFPS(10, 10);
      break;
    case ENDING:
      // TODO: update ending variables here
      break;
    default:
      break;
    }

    EndDrawing();
    //--------------------------------------------------------
  }

  // De-initialization
  // TODO: unload all loaded data (textures, fonts, audio) here
  CloseWindow();

  return 0;
}
