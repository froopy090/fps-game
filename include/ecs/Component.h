#pragma once
#include <raylib.h>

// TODO: add all of our structs

struct Position {
  float x;
  float y;
  float z;
};

struct Velocity {
  float dx;
  float dy;
  float dz;
};

struct Size {
  float x;
  float y;
  float z;
};

struct ViewCamera{
  Camera3D camera;
  int cameraMode;
};
