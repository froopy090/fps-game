#include "Entities/Pistol.h"
#include "Entities/Player.h"
#include "Utility/CameraHUD.h"
#include "World/TestMap.h"
#include "globals.h"
#include "raylib.h"
#include "raymath.h"
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

  // World
  auto testMap = std::make_unique<World::TestMap>();

  // Loading Entities
  auto pistol = std::make_unique<Entities::Pistol>();
  auto player1 = std::make_unique<Entities::Player>();

  // Utility objects
  auto cameraHUD = std::make_unique<Utility::CameraHUD>();

  // Testing
  Vector3 startPoint;
  Vector3 endPoint;
  Vector3 rayDir;
  Ray hitscanRay;


  //--------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) {
    // Events
    // --------------------------------------------------------
    pistol->Event();
    player1->Event();

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
      player1->Update();

      // Creating hitscan ray
      startPoint = player1->GetPosition();
      endPoint = player1->camera.target;

      rayDir = Vector3Subtract(endPoint, startPoint);
      hitscanRay = {startPoint, Vector3Normalize(rayDir)};


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
      pistol->Draw(player1.get());

      // Debug stuff
      cameraHUD->Draw(player1.get());
      DrawFPS(10, 10);

      BeginMode3D(player1->camera);
      //DrawLine3D(player1->GetPosition(),player1->camera.target, RED);
      DrawRay(hitscanRay, RED);
      EndMode3D();

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
