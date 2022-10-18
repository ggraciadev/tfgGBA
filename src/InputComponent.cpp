#include "InputComponent.h"

#include "bn_keypad.h"

InputComponent::InputComponent() : GameObjectComponent::GameObjectComponent() {
}

InputComponent::~InputComponent() {

}

void InputComponent::Start() {
    GameObjectComponent::Start();
}

void InputComponent::Update() {
    GameObjectComponent::Update();

    inputMovement = bn::fixed_point(0,0);
    if(bn::keypad::left_held()) {
        inputMovement.set_x(-1);
    }
    else if(bn::keypad::right_held()) {
        inputMovement.set_x(1);
    }
    if(bn::keypad::up_held()) {
        inputMovement.set_y(-1);
    }
    else if(bn::keypad::down_held()) {
        inputMovement.set_y(1);
    }
    movementComponent->SetInputMovement(inputMovement);
}

// void InputComponent::AddImpulse(bn::fixed_point impulse) {
//     velocity += impulse;
// }