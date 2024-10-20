# FPS Game

This is a simple FPS game project using `raylib`. Below are the instructions on how to compile and run the game.

## Compilation Instructions

To compile the project, follow these steps:

```sh
    mkdir build
    cd build
    cmake ..
    make
    ./fps-game
```

## Dependencies
- raylib library (to build raylib follow [these](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) instructions)
    - ensure libraylib.so, raylib.so.5.5.0, and raylib.so.550 is available in the lib directory
    - ensure raylib.h, raymath.h, and rlgl.h are in the include directory

## Acknowledgement
- [Francesco](https://github.com/froopy090)
    - Did most of the work
- [Elia](https://github.com/Thenewchicken55)
    - README.md
    - CMakeLists.txt
