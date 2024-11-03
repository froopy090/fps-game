cmake_minimum_required(VERSION 3.10)
project(fps-game)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

set(SOURCES
    src/main.cpp
    src/Entities/Pistol.cpp
    src/Entities/Player.cpp
    src/Entities/Enemy.cpp
    src/Utility/CameraHUD.cpp
    src/Utility/Timer.cpp
    src/Utility/PlayerInfoHUD.cpp
    src/World/Test002.cpp
    src/World/Room001.cpp
    src/World/BaseObjects.cpp
    src/World/LargeColumn.cpp
    src/World/Stairs.cpp
)

include_directories(include)

# Specify the library directory
link_directories(lib)

# Add the executable
add_executable(fps-game ${SOURCES})

# Link the raylib library and the math library
target_link_libraries(fps-game raylib m)

# Add run command
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release .
    COMMAND fps-game)

# Add GDB debug mode
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug .
    COMMAND ${CMAKE_COMMAND} --build .
    COMMAND gdb ./fps-game
)