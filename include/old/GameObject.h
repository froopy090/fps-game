#pragma once

// Abstract class for all objects in-game
class GameObject {
public:
  virtual ~GameObject() = default;

  virtual void Event() = 0;
  virtual void Update() = 0;
  virtual void Draw() = 0;
};
