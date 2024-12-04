#include "Entities/Enemy.h"
#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/CameraHUD.h"
#include "Utility/PlayerInfoHUD.h"
#include "Utility/WorldObjectManager.h"
#include "World/Room001.h"
#include "globals.h"
#include "raylib.h"
#include "resource_dir.h"
#include <dirent.h>
#include <memory>
#include "World/Room002.h"

#define MAX_COLUMNS 20

// Types and Structures Definition
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } Gamescreen;

int main() {
  // Initialization
  // ---------------------------------------------------------
  const int fps = 144;

  InitWindow(screenWidth, screenHeight, "fps");
  SetTargetFPS(fps);

  int framesCounter = 0;

  GameScreen currentScreen = LOGO;

  SearchAndSetResourceDir("resources");

  // Loading Entities
  auto player1 = std::make_unique<Entities::Player>();
  auto pistol = std::make_unique<Entities::Pistol>(player1.get());

  // Utility objects and managers
  auto cameraHUD = std::make_unique<Utility::CameraHUD>();
  auto playerInfoHUD = std::make_unique<Utility::PlayerInfoHUD>();
  auto enemyManager =
      std::make_unique<Utility::EnemyManager>(0, player1.get(), pistol.get());
  auto objectManager = std::make_unique<Utility::WorldObjectManager>(
      player1.get(), enemyManager.get());

  // World
  auto room = std::make_unique<World::Room002>(
      player1.get(), enemyManager.get(), objectManager.get());

  //--------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) {
    // Events
    // --------------------------------------------------------
    pistol->Event();
    player1->Event();
    enemyManager->Event();

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
      pistol->Update();
      player1->Update();
      enemyManager->Update();

      room->Update();
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
      room->Draw();

      enemyManager->Draw();
      player1->Draw();
      pistol->Draw();

      // HUD
      cameraHUD->Draw(player1.get());
      playerInfoHUD->Draw(player1.get());
      DrawFPS(5, 5);

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
