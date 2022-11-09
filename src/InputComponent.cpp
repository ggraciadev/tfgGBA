#include "InputComponent.h"

#include "bn_keypad.h"
#include "Character.h"

InputComponent::InputComponent() : GameObjectComponent::GameObjectComponent() {
}

InputComponent::~InputComponent() {

}

void InputComponent::Start() {
    updateType = UpdateType::LOGIC_UPDATE;
    GameObjectComponent::Start();
}

void InputComponent::Update() {
    GameObjectComponent::Update();

    if(bn::keypad::a_pressed()) {
        character->Jump();
    }

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
    character->SetInputMovement(inputMovement);

}

// void InputComponent::AddImpulse(bn::fixed_point impulse) {
//     velocity += impulse;
// }