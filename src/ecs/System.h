#pragma once

class Registry; // forward declaration

// base system interface
class System {
public:
    virtual ~System() = default;

    virtual void update(Registry& registry, float deltaTime) = 0;
};
