#include "World/Room001.h"
#include "Entities/Enemy.h"
#include "Entities/Player.h"
#include "Utility/Collision.h"
#include "raymath.h"
#include <iostream>
#include <math.h>

namespace World {
const int Room001::roomMatrix[ROOM_SIZE][ROOM_SIZE] = {
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Room001::Room001() {
  // Calculate center of matrix
  int center = ROOM_SIZE / 2;

  // Populate floors and walls
  for (int i = 0; i < ROOM_SIZE; i++) {
    for (int j = 0; j < ROOM_SIZE; j++) {
      // calulating position of tile
      float x = (i - center) * (-TILE_SIZE);
      float z = (j - center) * (-TILE_SIZE);
      Vector3 position = {x, 0.0f, z};

      if (roomMatrix[i][j] == 0) {
        floors.emplace_back(position);
      } else if (roomMatrix[i][j] == 1) {
        walls.emplace_back(position);
      } else if (roomMatrix[i][j] == 2) {
        columns.emplace_back(position);
      } else if (roomMatrix[i][j] == 3) {
        stairs.emplace_back(position);
      }
    }
  }
}

void Room001::Update(Entities::Player *player, Entities::Enemy *enemy) {
  // Reset
  player->SetPlaneCollision(false);
  enemy->SetPlaneCollision(false);
  // Checks collision between plane and Player
  for (Plane &floor : floors) {
    if (Utility::EntityCollisionObject(player, &floor)) {
      Utility::LockEntityAxis(player, &floor);
    }
    if (Utility::EntityCollisionObject(enemy, &floor)) {
      Utility::LockEntityAxis(enemy, &floor);
    }
  }

  // Checks wall collision for player and enemy
  for (Cube &wall : walls) {
    if (Utility::EntityCollisionObject(player, &wall)) {
      Utility::LockEntityAxis(player, &wall);
    }
    if (Utility::EntityCollisionObject(enemy, &wall)) {
      Utility::LockEntityAxis(enemy, &wall);
    }
  }

  // Checks collision between large columns and Player
  for (LargeColumn &column : columns) {
    if (Utility::EntityCollisionObject(player, &column)) {
      Utility::LockEntityAxis(player, &column);
    }
    if (Utility::EntityCollisionObject(enemy, &column)) {
      Utility::LockEntityAxis(enemy, &column);
    }
  }

  // Checks collision between stairs and player
  for (Stairs &stair : stairs) {
    Cube stairWall = stair.GetStairWall();
    if (Utility::EntityCollisionObject(player, &stairWall)) {
      Utility::LockEntityAxis(player, &stairWall);
    }
    if (Utility::EntityCollisionObject(enemy, &stairWall)) {
      Utility::LockEntityAxis(enemy, &stairWall);
    }
    std::vector<Cube> stairCubes = stair.GetCubeVector();
    for (Cube &stairCube : stairCubes) {
      if (Utility::EntityCollisionObject(player, &stairCube)) {
        Utility::LockEntityAxis(player, &stairCube);
      }
      if (Utility::EntityCollisionObject(enemy, &stairCube)) {
        Utility::LockEntityAxis(enemy, &stairCube);
      }
    }
  }
}

void Room001::Draw() {
  for (Plane &floor : floors) {
    floor.Draw();
  }
  for (Cube &wall : walls) {
    wall.Draw();
  }
  for (LargeColumn &column : columns) {
    column.Draw();
  }
  for (Stairs &stair : stairs) {
    stair.Draw();
  }
}
} // namespace World
