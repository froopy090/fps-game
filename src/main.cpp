#include <Game.h>
#include <raylib.h>

// Main ---------------------------------------------------
int main() {
  // Init
  GameState game;
  InitGame(&game);

  // Game loop
  while (!WindowShouldClose()) {
    UpdateGame(&game);
    DrawGame(&game);
  }

  // Shutdown
  CloseGame(&game);
  return 0;
}
// --------------------------------------------------------
