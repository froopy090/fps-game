#pragma once

namespace Utility {
class Timer {
private:
  float lifetime;
  float startTime;

public:
  void Start(float lifetime);
  bool Finished();
  bool Active();
  void Update();
  void PrintTime();
};
} // namespace Utility
