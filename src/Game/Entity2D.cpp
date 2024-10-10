#include "Game/Entity2D.h"
#include <raylib.h>

namespace Game {
Entity2D::Entity2D(Texture2D texture, Rectangle source, Rectangle destination,
                   Vector2 origin, float rotation)
    : texture(texture), source(source), destination(destination),
      origin(origin), rotation(rotation) {}

Entity2D::~Entity2D(){
    UnloadTexture(texture);
}

void Entity2D::Event(){}

void Entity2D::Update(){}

void Entity2D::Draw(){
    DrawTexturePro(texture, source, destination, origin, rotation, WHITE);
}
} // namespace Game
