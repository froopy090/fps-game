#include "World/BaseObjects.h"
#include "World/WorldDefinitions.h"
#include "iostream"
#include "raymath.h"
#include "rlgl.h"

namespace World {
// Cube --------------------------------------
std::unique_ptr<WorldTexture> Cube::texture = nullptr;

Cube::Cube() {
  // default constructor
  position = Vector3Zero();
  size = Vector3Zero();
  color = BLACK;
  box.min = Vector3Zero();
  box.max = Vector3Zero();

  if (!texture) {
    texture = std::make_unique<WorldTexture>();
    texture->texture = LoadTexture("metal.png");
  }
}

/*Cube::~Cube() { UnloadTexture(texture); }*/

Cube::Cube(Vector3 position) {
  // Init
  this->position =
      Vector3Add(position, (Vector3){0.0f, WALL_HEIGHT / 2.0f, 0.0f});
  size = (Vector3){TILE_SIZE, WALL_HEIGHT, TILE_SIZE};
  color = WHITE;
  box.min = (Vector3){position.x - size.x / 2.0f, position.y,
                      position.z - size.z / 2.0f};
  box.max = (Vector3){position.x + size.x / 2.0f, position.y + size.y,
                      position.z + size.z / 2.0f};

  if (!texture) {
    texture = std::make_unique<WorldTexture>();
    texture->texture = LoadTexture("metal.png");
  }
}

Cube::Cube(Vector3 position, Vector3 size) {
  // Init
  this->size = size;
  this->position = Vector3Add(position, (Vector3){0.0f, size.y / 2.0f, 0.0f});
  color = DARKGRAY;
  this->SetBoundingBox();

  if (!texture) {
    texture = std::make_unique<WorldTexture>();
    texture->texture = LoadTexture("metal.png");
  }
}

void Cube::Event() {}

void Cube::Update() {}

void Cube::Draw() {
  DrawCubeV(position, size, color);
  DrawBoundingBox(box, BLACK);
}

void Cube::DrawCubeTexture() {
  float x = position.x;
  float y = position.y;
  float z = position.z;

  float width = size.x;
  float height = size.y;
  float length = size.z;

  // Set desired texture to be enabled while drawing following vertex data
  rlSetTexture(texture->texture.id);

  // Vertex data transformation can be defined with the commented lines,
  // but in this example we calculate the transformed vertex data directly when
  // calling rlVertex3f()
  // rlPushMatrix();
  // NOTE: Transformation is applied in inverse order (scale -> rotate ->
  // translate)
  // rlTranslatef(2.0f, 0.0f, 0.0f);
  // rlRotatef(45, 0, 1, 0);
  // rlScalef(2.0f, 2.0f, 2.0f);

  rlBegin(RL_QUADS);
  rlColor4ub(color.r, color.g, color.b, color.a);
  // Front Face
  rlNormal3f(0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z + length / 2); // Bottom Left Of The Texture and Quad
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z + length / 2); // Bottom Right Of The Texture and Quad
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z + length / 2); // Top Right Of The Texture and Quad
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z + length / 2); // Top Left Of The Texture and Quad
  // Back Face
  rlNormal3f(0.0f, 0.0f, -1.0f); // Normal Pointing Away From Viewer
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z - length / 2); // Bottom Right Of The Texture and Quad
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z - length / 2); // Top Right Of The Texture and Quad
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z - length / 2); // Top Left Of The Texture and Quad
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z - length / 2); // Bottom Left Of The Texture and Quad
  // Top Face
  rlNormal3f(0.0f, 1.0f, 0.0f); // Normal Pointing Up
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z - length / 2); // Top Left Of The Texture and Quad
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z + length / 2); // Bottom Left Of The Texture and Quad
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z + length / 2); // Bottom Right Of The Texture and Quad
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z - length / 2); // Top Right Of The Texture and Quad
  // Bottom Face
  rlNormal3f(0.0f, -1.0f, 0.0f); // Normal Pointing Down
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z - length / 2); // Top Right Of The Texture and Quad
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z - length / 2); // Top Left Of The Texture and Quad
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z + length / 2); // Bottom Left Of The Texture and Quad
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z + length / 2); // Bottom Right Of The Texture and Quad
  // Right face
  rlNormal3f(1.0f, 0.0f, 0.0f); // Normal Pointing Right
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z - length / 2); // Bottom Right Of The Texture and Quad
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z - length / 2); // Top Right Of The Texture and Quad
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z + length / 2); // Top Left Of The Texture and Quad
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z + length / 2); // Bottom Left Of The Texture and Quad
  // Left Face
  rlNormal3f(-1.0f, 0.0f, 0.0f); // Normal Pointing Left
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z - length / 2); // Bottom Left Of The Texture and Quad
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z + length / 2); // Bottom Right Of The Texture and Quad
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z + length / 2); // Top Right Of The Texture and Quad
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z - length / 2); // Top Left Of The Texture and Quad
  rlEnd();
  // rlPopMatrix();

  rlSetTexture(0);
}

// Getters
Vector3 Cube::GetPosition() { return position; }

Vector3 Cube::GetSize() { return size; }

Color Cube::GetColor() { return color; }

BoundingBox Cube::GetBoundingBox() { return box; }

// Setters
void Cube::SetPosition(Vector3 position) {
  this->position = position;
  // update the bounding box position
  this->SetBoundingBox();
}

void Cube::SetSize(Vector3 size) {
  this->size = size;
  // update the boudning box size
  this->SetBoundingBox();
}

void Cube::SetColor(Color color) { this->color = color; }

// Helper Functions
void Cube::SetBoundingBox() {
  box.min = (Vector3){position.x - size.x / 2.0f, position.y - size.y / 2.0f,
                      position.z - size.z / 2.0f};
  box.max = (Vector3){position.x + size.x / 2.0f, position.y + size.y / 2.0f,
                      position.z + size.z / 2.0f};
}
// End Cube ---------------------------------------------------------
//
// Plane ---------------------------------------------------------
std::unique_ptr<WorldTexture> Plane::texture = nullptr;

Plane::Plane(Vector3 position) {
  // Init
  this->position = position;
  size = (Vector2){TILE_SIZE, TILE_SIZE};
  color = GRAY;
  box.min = (Vector3){position.x - size.x / 2.0f, position.y,
                      position.z - size.y / 2.0f};
  box.max = (Vector3){position.x + size.x / 2.0f, position.y,
                      position.z + size.y / 2.0f};
  if (!texture) {
    texture = std::make_unique<WorldTexture>();
    texture->texture = LoadTexture("concrete.png");
  }
}

void Plane::Event() {}

void Plane::Update() {}

void Plane::Draw() {
  DrawPlane(position, size, color);
  DrawBoundingBox(box, BLACK);
}

void Plane::DrawPlaneTexture() {
  float x = position.x;
  float y = position.y;
  float z = position.z;

  float width = size.x;
  float length= size.y;
  float height = position.y;

  // Set desired texture to be enabled while drawing following vertex data
  rlSetTexture(texture->texture.id);

  // Vertex data transformation can be defined with the commented lines,
  // but in this example we calculate the transformed vertex data directly when
  // calling rlVertex3f()
  // rlPushMatrix();
  // NOTE: Transformation is applied in inverse order (scale -> rotate ->
  // translate)
  // rlTranslatef(2.0f, 0.0f, 0.0f);
  // rlRotatef(45, 0, 1, 0);
  // rlScalef(2.0f, 2.0f, 2.0f);

  rlBegin(RL_QUADS);
  rlColor4ub(color.r, color.g, color.b, color.a);
  // Top Face
  rlNormal3f(0.0f, 1.0f, 0.0f); // Normal Pointing Up
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z - length / 2); // Top Left Of The Texture and Quad
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x - width / 2, y + height / 2,
             z + length / 2); // Bottom Left Of The Texture and Quad
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z + length / 2); // Bottom Right Of The Texture and Quad
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x + width / 2, y + height / 2,
             z - length / 2); // Top Right Of The Texture and Quad
  // Bottom Face
  rlNormal3f(0.0f, -1.0f, 0.0f); // Normal Pointing Down
  rlTexCoord2f(1.0f, 1.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z - length / 2); // Top Right Of The Texture and Quad
  rlTexCoord2f(0.0f, 1.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z - length / 2); // Top Left Of The Texture and Quad
  rlTexCoord2f(0.0f, 0.0f);
  rlVertex3f(x + width / 2, y - height / 2,
             z + length / 2); // Bottom Left Of The Texture and Quad
  rlTexCoord2f(1.0f, 0.0f);
  rlVertex3f(x - width / 2, y - height / 2,
             z + length / 2); // Bottom Right Of The Texture and Quad
  rlEnd();
  // rlPopMatrix();

  rlSetTexture(0);
}

// Getters
Vector3 Plane::GetPosition() { return position; }

Vector2 Plane::GetSize() { return size; }

Color Plane::GetColor() { return color; }

BoundingBox Plane::GetBoundingBox() { return box; }

// Setters
void Plane::SetPosition(Vector3 position) { this->position = position; }

void Plane::SetSize(Vector2 size) { this->size = size; }

void Plane::SetColor(Color color) { this->color = color; }

void Plane::SetBoundingBox(BoundingBox box) { this->box = box; }
// End Plane -----------------------------------------------------
} // namespace World
