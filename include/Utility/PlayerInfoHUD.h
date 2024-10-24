#pragma once
#include "Entities/Player.h"
#include "raylib.h"

namespace Utility {
class PlayerInfoHUD {
    public:
        void Draw(Entities::Player *player);
};
} // namespace Utility
