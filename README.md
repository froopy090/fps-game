# FPS Game - CORE REWORK BRANCH 

This branch is work in progress. Here are some of the major changes to be done:
- optimization overhaul
- core structure of the project will be ECS-inspired
    - ECS (entity-component-system) you can check out the wikipedia page [here](https://en.wikipedia.org/wiki/Entity_component_system)
- massive code clean up
- in short, the code is a mess, let's fix it up

## Progress Video
[![Watch the video](https://img.youtube.com/vi/F_vNK2XNKvg/hqdefault.jpg)](https://www.youtube.com/watch?v=F_vNK2XNKvg)


## Compilation Instructions

To compile the project, follow these steps:

```sh
    mkdir build
    cd build
    cmake ..
    make run
```

## Dependencies
- raylib library (to build raylib follow [these](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) instructions)
    - ensure libraylib.so, raylib.so.5.5.0, and raylib.so.550 is available in the lib directory (if you don't have a lib directory, make it)
    - ensure raylib.h, raymath.h, and rlgl.h are in the include directory

## Acknowledgement
- [Francesco](https://github.com/froopy090)
    - Did most of the work
- [Elia](https://github.com/Thenewchicken55)
    - README.md
    - CMakeLists.txt
    - Some random stuff
