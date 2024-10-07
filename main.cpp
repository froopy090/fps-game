#include "raylib.h"

//Types and Structures Definition
typedef enum GameScreen {LOGO = 0, TITLE, GAMEPLAY, ENDING} Gamescreen;

int main(){
    //Initialization
    const int screenWidth = 500;
    const int screenHeight = 500;
    const int fps = 60;

    InitWindow(screenWidth, screenHeight, "fps");
    SetTargetFPS(fps);

    int framesCounter = 0;

    GameScreen currentScreen = LOGO;

    //Main game loop
    while(!WindowShouldClose()){
        //Update
        switch(currentScreen){
            case LOGO:
                framesCounter++;
                if(framesCounter > fps*4){
                    currentScreen = TITLE;
                }
                break;
            case TITLE:

        }


        //Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("epic text", 250, 250, 32, WHITE);
        EndDrawing();
    }

    //De-initialization
    CloseWindow();

    return 0;
}
