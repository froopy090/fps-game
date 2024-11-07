#include "World/Room001.h"
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
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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

bool xAxisCollision(Entities::Player *playa, World::Cube &IceCube) {
  return playa->GetBoundingBox().min.x < IceCube.GetBoundingBox().min.x ||
         playa->GetBoundingBox().max.x > IceCube.GetBoundingBox().max.x;
}

bool zAxisCollision(Entities::Player *playa, World::Cube &IceCube) {
  return playa->GetBoundingBox().min.z < IceCube.GetBoundingBox().min.z ||
         playa->GetBoundingBox().max.z > IceCube.GetBoundingBox().max.z;
}

void lockAxis(Entities::Player *playa, World::Cube &IceCube) {
  // this is the exception, where player is in the corner
  // if we have collision on BOTH axiis
  if (xAxisCollision(playa, IceCube) && zAxisCollision(playa, IceCube)) {
    if (abs(playa->GetVelocity().x) > 0.0f) {
      playa->camera.position.x = playa->GetPreviousPosition().x;
    } else if (abs(playa->GetVelocity().z) > 0.0f) {
      playa->camera.position.z = playa->GetPreviousPosition().z;
    }
    // return; // dr carbon, absolute legend
  } else if (xAxisCollision(playa, IceCube)) {
    playa->camera.position.x = playa->GetPreviousPosition().x;
  } else if (zAxisCollision(playa, IceCube)) {
    playa->camera.position.z = playa->GetPreviousPosition().z;
  }
}

void Room001::Update(Entities::Player *player) {
  // Reset
  player->SetPlaneCollision(false);
  // Checks collision between plane and Player
  for (Plane &floor : floors) {
    if (Utility::EntityCollisionObject(player, &floor)) {
      player->SetPlaneCollision(true);
      break;
    }
  }

  // Checks collision between walls and Player
  for (Cube &wall : walls) {
    if (Utility::EntityCollisionObject(player, &wall)) {
      // if player's bottom half is inside wall
      if (player->GetBoundingBox().min.y < wall.GetBoundingBox().max.y &&
          player->GetBoundingBox().max.y > wall.GetBoundingBox().max.y) {
        player->camera.position.y =
            wall.GetBoundingBox().max.y + player->GetSize().y;
      } else { // else prevent them from phasing into wall
        lockAxis(player, wall);
      }
      player->SetPlaneCollision(true);
    }
  }

  // Checks collision between walls and Player
  for (LargeColumn &column : columns) {
    if (Utility::EntityCollisionObject(player, &column)) {
      player->camera.position = player->GetPreviousPosition();
    }
  }

  // only execute this at 60 fps (once every 60 frames)
  // Checks collision between stairs and player
  for (Stairs &stair : stairs) {
    std::vector<Cube> stairCubes = stair.GetCubeVector();
    for (Cube &stairCube : stairCubes) {
      // if player is colliding and player is below the stair height
      if (Utility::EntityCollisionObject(player, &stairCube)) {
        player->camera.position.y =
            stairCube.GetBoundingBox().max.y + player->GetSize().y;
        player->SavePosition();
        player->SetPlaneCollision(true);
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
