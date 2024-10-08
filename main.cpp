#include "raylib.h"

#define MAX_COLUMNS 20

// Types and Structures Definition
typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } Gamescreen;

int main() {
  // Initialization
  // ---------------------------------------------------------
  const int screenWidth = 600;
  const int screenHeight = 600;
  const int fps = 60;

  InitWindow(screenWidth, screenHeight, "fps");
  SetTargetFPS(fps);

  int framesCounter = 0;

  GameScreen currentScreen = LOGO;

  // camera Definition
  Camera camera{0};
  camera.position = (Vector3){0.0f, 2.0f, 4.0f}; // camera position
  camera.target = (Vector3){0.0f, 0.0f, 0.0f};     // camera looking at point
  camera.up =
      (Vector3){0.0f, 1.0f, 0.0f}; // camera up vector (rotation towards target)
  camera.fovy = 90.0f;             // camera field of view Y
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

  //--------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) {
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
     UpdateCameraPro(&camera,
            (Vector3){
                (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))*0.1f -      // Move forward-backward
                (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))*0.1f,    
                (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))*0.1f -   // Move right-left
                (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))*0.1f,
                0.0f                                                // Move up-down
            },
            (Vector3){
                GetMouseDelta().x*0.05f,                            // Rotation: yaw
                GetMouseDelta().y*0.05f,                            // Rotation: pitch
                0.0f                                                // Rotation: roll
            },
            GetMouseWheelMove()*2.0f);                              // Move to target (zoom) 

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
      EndMode3D();
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
