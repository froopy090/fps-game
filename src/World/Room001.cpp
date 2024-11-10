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

bool xAxisCollision(Entities::Player *playa, World::Cube &IceCube) {
  return playa->GetBoundingBox().min.x < IceCube.GetBoundingBox().min.x ||
         playa->GetBoundingBox().max.x > IceCube.GetBoundingBox().max.x;
}

bool zAxisCollision(Entities::Player *playa, World::Cube &IceCube) {
  return playa->GetBoundingBox().min.z < IceCube.GetBoundingBox().min.z ||
         playa->GetBoundingBox().max.z > IceCube.GetBoundingBox().max.z;
}

void lockXAxis(Entities::Player *player) {
  player->camera.position.x = player->GetPreviousPosition().x;
}

void lockZAxis(Entities::Player *player) {
  player->camera.position.z = player->GetPreviousPosition().z;
}

void lockAxis(Entities::Player *playa, World::Cube &IceCube) {
  // this is the exception, where player is in the corner
  // if we have collision on BOTH axiis
  if (xAxisCollision(playa, IceCube) && zAxisCollision(playa, IceCube)) {
    // case 1, xVel > 0, zVel < 0
    if (playa->GetVelocity().x > 0.0f && playa->GetVelocity().z < 0.0f) {
      std::cout << "Case 1" << std::endl;
      // bottom right corner
      if (playa->GetBoundingBox().min.x <= IceCube.GetBoundingBox().min.x &&
          playa->GetBoundingBox().min.z < IceCube.GetBoundingBox().min.z) {
        std::cout << "bottom right" << std::endl;
        lockXAxis(playa);
        return;
      }
      // top left corner
      if (playa->GetBoundingBox().max.z >= IceCube.GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x > IceCube.GetBoundingBox().max.x) {
        std::cout << "top left" << std::endl;
        lockZAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().min.x + playa->GetSize().x >
              IceCube.GetBoundingBox().max.x - IceCube.GetSize().x + 0.1f &&
          playa->GetBoundingBox().min.z <
              IceCube.GetBoundingBox().max.z - 0.1f &&
          playa->GetBoundingBox().min.x + playa->GetSize().x <
              IceCube.GetBoundingBox().max.x - IceCube.GetSize().x + 0.5f &&
          playa->GetBoundingBox().min.z >
              IceCube.GetBoundingBox().max.z - 0.5f) {
        lockXAxis(playa);
        lockZAxis(playa);
      }
    }

    // case 2, xVel < 0, zVel > 0
    if (playa->GetVelocity().x < 0.0f && playa->GetVelocity().z > 0.0f) {
      std::cout << "Case 2" << std::endl;
      // bottom right corner
      if (playa->GetBoundingBox().min.x <= IceCube.GetBoundingBox().min.x &&
          playa->GetBoundingBox().min.z < IceCube.GetBoundingBox().min.z) {
        std::cout << "bottom right" << std::endl;
        lockZAxis(playa);
        return;
      }
      // top left corner
      if (playa->GetBoundingBox().max.z >= IceCube.GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x > IceCube.GetBoundingBox().max.x) {
        std::cout << "top left" << std::endl;
        lockXAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().max.x - playa->GetSize().x <
              IceCube.GetBoundingBox().min.x + IceCube.GetSize().x - 0.1f &&
          playa->GetBoundingBox().max.z >
              IceCube.GetBoundingBox().min.z + 0.1f &&
          playa->GetBoundingBox().max.x - playa->GetSize().x >
              IceCube.GetBoundingBox().min.x + IceCube.GetSize().x - 0.5f &&
          playa->GetBoundingBox().max.z <
              IceCube.GetBoundingBox().min.z + 0.5f) {
        lockXAxis(playa);
        lockZAxis(playa);
      }
    }

    // case 3, xVel < 0, zVel < 0
    if (playa->GetVelocity().x < 0.0f && playa->GetVelocity().z < 0.0f) {
      std::cout << "Case 3" << std::endl;
      // top right corner
      if (playa->GetBoundingBox().max.z >= IceCube.GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x < IceCube.GetBoundingBox().max.x &&
          playa->GetBoundingBox().max.x > IceCube.GetBoundingBox().min.x) {
        std::cout << "top right" << std::endl;
        lockZAxis(playa);
        return;
      }
      // bottom left corner
      if (playa->GetBoundingBox().max.x >= IceCube.GetBoundingBox().max.x &&
          playa->GetBoundingBox().max.z < IceCube.GetBoundingBox().max.z) {
        std::cout << "bottom left" << std::endl;
        lockXAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().min.x <
              IceCube.GetBoundingBox().max.x - 0.1f &&
          playa->GetBoundingBox().min.z <
              IceCube.GetBoundingBox().max.z - 0.1f &&
          playa->GetBoundingBox().min.x >
              IceCube.GetBoundingBox().max.x - 0.5f &&
          playa->GetBoundingBox().min.z >
              IceCube.GetBoundingBox().max.z - 0.5f) {
        lockXAxis(playa);
        lockZAxis(playa);
      }
    }

    // case 4, xVel > 0, zVel > 0
    if (playa->GetVelocity().x > 0.0f && playa->GetVelocity().z > 0.0f) {
      std::cout << "Case 4" << std::endl;
      // top right corner
      if (playa->GetBoundingBox().max.z >= IceCube.GetBoundingBox().max.z &&
          playa->GetBoundingBox().max.x < IceCube.GetBoundingBox().max.x) {
        std::cout << "top right" << std::endl;
        lockXAxis(playa);
        return;
      }
      // bottom left corner
      if (playa->GetBoundingBox().max.x >= IceCube.GetBoundingBox().max.x &&
          playa->GetBoundingBox().max.z < IceCube.GetBoundingBox().max.z) {
        std::cout << "bottom left" << std::endl;
        lockZAxis(playa);
        return;
      }
      // check to see if we went inside of the corner
      // if we did, lock both axiis
      if (playa->GetBoundingBox().max.x >
              IceCube.GetBoundingBox().min.x + 0.1f &&
          playa->GetBoundingBox().max.z >
              IceCube.GetBoundingBox().min.z + 0.1f &&
          playa->GetBoundingBox().max.x <
              IceCube.GetBoundingBox().min.x + 0.5f &&
          playa->GetBoundingBox().max.z <
              IceCube.GetBoundingBox().min.z + 0.5f) {
        lockXAxis(playa);
        lockZAxis(playa);
      }
    }
    // return; // dr carbon, absolute legend
  } else if (xAxisCollision(playa, IceCube)) {
    lockXAxis(playa);
  } else if (zAxisCollision(playa, IceCube)) {
    lockZAxis(playa);
  } else {
    std::cout << "all collision checks failed" << std::endl;
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
      /*if (player->GetBoundingBox().min.y < wall.GetBoundingBox().max.y &&*/
      /*    player->GetBoundingBox().max.y > wall.GetBoundingBox().max.y) {*/
      /*  player->SetPlaneCollision(true);*/
      /*  player->camera.position.y =*/
      /*      wall.GetBoundingBox().max.y + player->GetSize().y;*/
      /*} */
      // if player is on top of box
      if (player->GetBoundingBox().max.y >= wall.GetBoundingBox().max.y) {
        player->camera.position.y =
            wall.GetBoundingBox().max.y + player->GetSize().y;
        player->SetPlaneCollision(true);
      } else { // else prevent them from phasing into wall
        lockAxis(player, wall);
      }
    }
  }

  // Checks collision between walls and Player
  for (LargeColumn &column : columns) {
    if (Utility::EntityCollisionObject(player, &column)) {
      player->camera.position = player->GetPreviousPosition();
    }
  }

  // Checks collision between stairs and player
  for (Stairs &stair : stairs) {
    std::vector<Cube> stairCubes = stair.GetCubeVector();
    for (Cube &stairCube : stairCubes) {
      // if player is colliding and player is below the stair height
      if (Utility::EntityCollisionObject(player, &stairCube)) {
        player->camera.position.y =
            stairCube.GetBoundingBox().max.y + player->GetSize().y;
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
