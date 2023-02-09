#include "GameObjectComponents/InputComponent.h"

#include "bn_keypad.h"
#include "Player.h"

void InputComponent::Start() {
    updateType = UpdateType::PHYSICS_UPDATE;
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
    player->SetInputMovement(inputMovement);

    if(bn::keypad::a_pressed()) {
        player->Attack();
    }
    else if(bn::keypad::b_pressed()) {
        player->Jump();
    }
    else if(bn::keypad::r_pressed()) {
        player->Dash();
    }

}

// void InputComponent::AddImpulse(bn::fixed_point impulse) {
//     velocity += impulse;
// }