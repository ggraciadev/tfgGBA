#include "GameObjectComponents/MovementComponent.h"
#include "GameObjects/GameObject.h"

void MovementComponent::Start() {
    GameObjectComponent::Start();
    velocity = bn::fixed_point(0,0);
    gravityValue = 0.2f;
    movementDirection = 1;
}

void MovementComponent::Update() {
    GameObjectComponent::Update();
    CalcVelocity();
    CheckCollisions();
    gameObject->AddLocalOffset(velocity);
}

void MovementComponent::CalcVelocity() {
    if(currentImpulseDuration > 0) {
        currentImpulseDuration--;
        return;
    }
    velocity.set_x(currentMovementSpeed * inputMovement.x());
    if(gravityValue != 0) {
        if(!isGrounded) {
            velocity.set_y(velocity.y() + gravityValue);
        }
    }
    else {
        velocity.set_y(currentMovementSpeed * inputMovement.y());
    }
    if(inputMovement.x() > 0 && velocity.x() > 0) {
        movementDirection = 1;
    }
    else if(inputMovement.x() < 0 && velocity.x() < 0) {
        movementDirection = -1;
    }
}

void MovementComponent::CheckCollisions() const {

}

void MovementComponent::SetGrounded(bool g) {
    if(g != isGrounded) {
        isGrounded = g;
        if(isGrounded) {
            velocity.set_y(0);
        }
    }
}

void MovementComponent::AddImpulse(bn::fixed_point impulse, int impulseDuration) {
    currentImpulseDuration = impulseDuration;
    velocity = impulse;
}
