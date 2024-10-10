#include "Utility/Timer.h"
#include "raylib.h"

namespace Utility {
void Timer::Start(float lifetime) { this->lifetime = lifetime; }

bool Timer::Finished() { return lifetime <= 0; }

void Timer::Update() {
  if (lifetime > 0) {
    lifetime -= GetFrameTime();
  }
}
} // namespace Utility
