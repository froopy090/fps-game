#pragma once

class Registry; // forward declaration

// base system interface
class System {
public:
    virtual ~System() = default;

    virtual void Update(Registry& registry) = 0;
};
