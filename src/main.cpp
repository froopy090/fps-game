#include "Entities/Pistol.h"
#include "globals.h"
#include "raylib.h"
#include <dirent.h>
#include <memory>
#include "raymath.h"

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

  // camera Definition
  Camera3D camera{0};
  camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // camera position
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};   // camera looking at point
  camera.up = (Vector3){0.0f, 1.0f, 0.0f};       // camera up vector
  camera.fovy = 90.0f;                           // camera field of view Y
  camera.projection = CAMERA_PERSPECTIVE;
  int cameraMode = CAMERA_FIRST_PERSON;
  DisableCursor(); // limit cursor to relative movement inside the window

  // Generate some random columns
  float heights[MAX_COLUMNS] = {0};
  Vector3 positions[MAX_COLUMNS] = {0};
  Color colors[MAX_COLUMNS] = {0};

  for (int i = 0; i < MAX_COLUMNS; i++) {
    heights[i] = (float)GetRandomValue(1, 12);
    positions[i] = (Vector3){(float)GetRandomValue(-15, 15), heights[i] / 2.0f,
                             (float)GetRandomValue(-15, 15)};
    colors[i] =
        (Color){GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255};
  }

  // Loading Entities
  auto pistol = std::make_unique<Entities::Pistol>();


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

      UpdateCamera(&camera, cameraMode);
      
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

      BeginMode3D(camera);

      DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f},
                LIGHTGRAY); // draw ground
      DrawCube((Vector3){-16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
               BLUE); // draw blue wall
      DrawCube((Vector3){16.0f, 2.5f, 0.0f}, 1.0f, 5.0f, 32.0f,
               LIME); // draw green wall
      DrawCube((Vector3){0.0f, 2.5f, 16.0f}, 32.0f, 5.0f, 1.0f,
               GOLD); // draw yellow wall
      DrawGrid(10, 1.0f);

      // Draw some cubes around
      for (int i = 0; i < MAX_COLUMNS; i++) {
        DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
        DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
      }

      DrawLine3D(camera.position, camera.target, RED);

      EndMode3D();

      pistol->Draw();

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
