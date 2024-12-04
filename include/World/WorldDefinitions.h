#pragma once
#include "raylib.h"

namespace World {
// Room Objects
constexpr int TILE_SIZE = 5;
constexpr int WALL_HEIGHT = 3;

// Rooms
constexpr int ROOM_SIZE = 25;

// World Map
constexpr int MAP_SIZE = 5;

struct WorldTexture {
  Texture2D texture;
  ~WorldTexture() { UnloadTexture(texture); }
};
// Maps ints to constructors for world objects
} // namespace World
