#include "Actor.h"

Actor::Actor() : GameObject::GameObject() {

}

Actor::Actor(const int posX, const int posY, GameObject* _parent, const bn::fixed gravity) : GameObject::GameObject(posX, posY, _parent){
    gravityValue = gravity;
}

Actor::~Actor() {

}

void Actor::Start() {
    GameObject::Start();
}

void Actor::Update() {
    GameObject::Update();
    CalcVelocity();
    CheckCollisions();
    AddLocalOffset(velocity);
}

void Actor::CalcVelocity() {
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

void Actor::CheckCollisions() {

}

void Actor::SetGrounded(bool g) {
    isGrounded = g;
    velocity.set_y(0);
}

void Actor::AddImpulse(bn::fixed_point impulse) {
    velocity += impulse;
}

void Actor::Render() {
    GameObject::Render();
    sprite->set_position(GetScreenPosition());
}

