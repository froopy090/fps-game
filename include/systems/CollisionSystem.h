#pragma once

#include <Component.h>
#include <Registry.h>
#include <iostream>
#include <systems/System.h>

struct CollisionInfo {
  bool collided = false;
  enum class Direction {
    NONE,
    TOP,
    BOTTOM
  } direction = CollisionInfo::Direction::NONE;
  BoundingBox box1;
  BoundingBox box2;
};

class CollisionSystem : public System {
public:
  void Update(Registry &registry) override;

private:
  // Collision detection
  bool XAxisCollision();

  CollisionInfo YAxisCollision(BoundingBox box1, BoundingBox box2) {
    float tolerance = 0.05f;
    CollisionInfo result;
    result.box1 = box1;
    result.box2 = box2;

    if (box1.min.y - tolerance <= box2.max.y + tolerance &&
        box1.max.y + tolerance >= box2.min.y - tolerance) {
      result.collided = true;
      std::cout << "Collision detected" << std::endl;
    }

    if (box1.min.y - tolerance <= box2.max.y + tolerance) {
      result.direction = CollisionInfo::Direction::TOP;
      return result;
    }

    if (box1.max.y + tolerance >= box2.min.y - tolerance) {
      result.direction = CollisionInfo::Direction::BOTTOM;
      return result;
    }
    return result;
  }

  bool ZAxisCollision();

  // Axis locking
  void LockXAxis();
  void LockYAxis(TransformComponent &transform, VelocityComponent &velocity,
                 SizeComponent &size, GroundedComponent &grounded,
                 CollisionInfo collision) {
    if (collision.collided &&
        collision.direction == CollisionInfo::Direction::TOP) {
      transform.position.y = collision.box2.max.y + size.size.y;
      velocity.velocity.y = 0.0f;
      grounded.isGrounded = true;
      std::cout << "UP collision" << std::endl;
    }

    if (collision.collided &&
        collision.direction == CollisionInfo::Direction::BOTTOM) {
      transform.position.y = collision.box2.min.y - size.size.y;
      velocity.velocity.y = 0.0f;
      grounded.isGrounded = false;
      std::cout << "DOWN collision" << std::endl;
    }
  };
  void LockZAxis();
};
