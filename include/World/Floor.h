#pragma once
#include "raylib.h"

namespace World {
class Floor {
    public:
        Floor(Vector3 position);
        void Draw();
    private:
        Vector3 position;
        Vector2 dimension;
        Color color;
        BoundingBox box;
};
} // namespace World
