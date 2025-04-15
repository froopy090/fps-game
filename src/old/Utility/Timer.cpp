#include "Utility/Timer.h"
#include "raylib.h"
#include <iostream>

namespace Utility {
void Timer::Start(float lifetime) {
  startTime = lifetime;
  this->lifetime = lifetime;
}

bool Timer::Finished() { return lifetime <= 0; }

bool Timer::Active() {
  // if timer is still going
  // and if the startTime is not 0, AKA the timer exists
  if (lifetime > 0 && lifetime < startTime && startTime != 0.0f) {
    return true;
  }
  return false;
}

void Timer::Update() {
  if (lifetime > 0) {
    lifetime -= GetFrameTime();
  }
}

void Timer::PrintTime() { std::cout << "timer: " << lifetime << std::endl; }
} // namespace Utility
