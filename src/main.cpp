#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/CameraHUD.h"
#include "Utility/PlayerInfoHUD.h"
#include "World/TestMap.h"
#include "globals.h"
#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include <dirent.h>
#include <memory>

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

  SearchAndSetResourceDir("resources");

  // World
  auto testMap = std::make_unique<World::TestMap>();

  // Loading Entities
  auto pistol = std::make_unique<Entities::Pistol>();
  auto player1 = std::make_unique<Entities::Player>();
  auto enemy1 = std::make_unique<Entities::Enemy>(player1.get());

  // Utility objects
  auto cameraHUD = std::make_unique<Utility::CameraHUD>();
  auto playerInfoHUD = std::make_unique<Utility::PlayerInfoHUD>();

  //--------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) {
    // Events
    // --------------------------------------------------------
    pistol->Event();
    player1->Event();
    enemy1->Event();

    // --------------------------------------------------------
    // Update
    // --------------------------------------------------------
    switch (currentScreen) {
    case LOGO:
      framesCounter++;

      // waiting for 4 seconds
      // for debugging changed to 0
      if (framesCounter > fps * 0) {
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
      player1->Update(testMap.get());
      enemy1->Update(player1.get(), pistol.get());

      testMap->Update(player1.get(), enemy1.get());

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
      enemy1->Draw(player1.get());
      player1->Draw();
      pistol->Draw(player1.get());

      // HUD
      cameraHUD->Draw(player1.get());
      playerInfoHUD->Draw(player1.get());
      DrawFPS(screenWidth - 10, screenHeight - 10);

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
