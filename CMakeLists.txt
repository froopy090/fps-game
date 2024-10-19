cmake_minimum_required(VERSION 3.10)
project(fps-game)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
    src/Entities/Pistol.cpp
    src/Entities/Player.cpp
    src/Utility/CameraHUD.cpp
    src/Utility/Timer.cpp
    src/World/TestMap.cpp
)

include_directories(include)

# Specify the library directory
link_directories(lib)

# Add the executable
add_executable(MyProject ${SOURCES})

# Link the raylib library and the math library
target_link_libraries(MyProject raylib m)