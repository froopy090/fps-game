cmake_minimum_required(VERSION 3.10)
project(fps-game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.cpp
    src/ecs/systems/ViewCameraSystem.cpp
    src/ecs/systems/ModelRenderSystem.cpp
    src/ecs/systems/PhysicsSystem.cpp
    src/ecs/entities/PlayerFactory.cpp
    src/ecs/entities/EnvironmentFactory.cpp
    src/Game.cpp
)

include_directories(include)

# Specify the library directory
# link_directories(lib)

# Add the executable
add_executable(fps-game ${SOURCES})

# Link the raylib library and the math library
target_link_libraries(fps-game raylib m)

target_include_directories(fps-game PRIVATE ${CMAKE_SOURCE_DIR}/include)

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
