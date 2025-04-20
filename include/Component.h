#pragma once
#include <math.h>
#include <raylib.h>

// TODO: add all of our structs

struct ViewCameraComponent {
  Camera3D camera;
  int cameraMode;
};

struct ModelComponent {
  Model model;
  Texture2D texture;
};

struct TransformComponent {
  Vector3 position;
  // TODO: scale and rotation
};

struct SizeComponent {
  Vector3 size;
};

struct VelocityComponent {
  Vector3 velocity;
};

struct ColliderComponent {
  BoundingBox bounds;
  bool isStatic;

  Vector3 GetSize() const {
    float x = std::fabs(bounds.max.x - bounds.min.x);
    float y = std::fabs(bounds.max.y - bounds.min.y);
    float z = std::fabs(bounds.max.z - bounds.min.z);
    return {x, y, z};
  }
};
