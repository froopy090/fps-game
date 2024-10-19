# FPS Game

This is a simple FPS game project using `raylib`. Below is the project structure and instructions on how to compile and run the game.

## Compilation Instructions

To compile the project, follow these steps:

1. **Create a Build Directory**:
   ```sh
   mkdir build
cd build
cmake ..
make
./fps-game



## Project Structure
.
├── CMakeLists.txt
├── README.md
├── include
│   ├── Entities
│   │   ├── Pistol.h
│   │   └── Player.h
│   ├── Utility
│   │   ├── CameraHUD.h
│   │   └── Timer.h
│   ├── World
│   │   └── TestMap.h
│   ├── globals.h
│   ├── raylib.h
│   ├── raymath.h
│   ├── rcamera.h
│   ├── rgestures.h
│   └── rlgl.h
├── lib
│   ├── libraylib.so
│   ├── libraylib.so.5.5.0
│   └── libraylib.so.550
├── resources
│   ├── DOOM_Pistol_Cropped.png
│   ├── DOOM_Pistol_Uncropped.png
│   └── raylib_logo.png
└── src
    ├── Entities
    │   ├── Pistol.cpp
    │   └── Player.cpp
    ├── Utility
    │   ├── CameraHUD.cpp
    │   └── Timer.cpp
    ├── World
    │   └── TestMap.cpp
    └── main.cpp

10 directories, 25 files
