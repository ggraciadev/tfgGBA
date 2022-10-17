#include "MovementComponent.h"
#include "GameObject.h"

MovementComponent::MovementComponent() : GameObjectComponent::GameObjectComponent() {
}

MovementComponent::~MovementComponent() {

}

void MovementComponent::Start() {
    GameObjectComponent::Start();
}

void MovementComponent::Update() {
    GameObjectComponent::Update();
    CalcVelocity();
    CheckCollisions();
    gameObject->AddLocalOffset(1, 0);
}

void MovementComponent::CalcVelocity() {
    velocity.set_x(currentMovementSpeed * inputMovement.x());
    if(gravityValue != 0) {
        if(!isGrounded) {
            velocity.set_y(velocity.y() + gravityValue);
        }
    }
    else {
        velocity.set_y(currentMovementSpeed * inputMovement.y());
    }
}

void MovementComponent::CheckCollisions() {

}

void MovementComponent::SetGrounded(bool g) {
    isGrounded = g;
    velocity.set_y(0);
}

// void MovementComponent::AddImpulse(bn::fixed_point impulse) {
//     velocity += impulse;
// }