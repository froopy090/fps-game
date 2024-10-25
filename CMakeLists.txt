cmake_minimum_required(VERSION 3.10)
project(fps-game)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/Entities/Pistol.cpp
    src/Entities/Player.cpp
    src/Entities/Enemy.cpp
    src/Utility/CameraHUD.cpp
    src/Utility/Timer.cpp
    src/Utility/PlayerInfoHUD.cpp
    src/World/TestMap.cpp
    src/World/Test002.cpp
)

include_directories(include)

# Specify the library directory
link_directories(lib)

# Add the executable
add_executable(fps-game ${SOURCES})

# Link the raylib library and the math library
target_link_libraries(fps-game raylib m)
