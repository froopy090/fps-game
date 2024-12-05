#pragma once

namespace World {
class Room {
public:
  virtual void Update() = 0;
  virtual void Draw() = 0;
};
} // namespace World
