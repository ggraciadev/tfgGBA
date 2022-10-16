#include "PlayerController.h"
#include "bn_keypad.h"

PlayerController::PlayerController() {

}

PlayerController::~PlayerController() {

}

void PlayerController::Start() {
    PawnController::Start();
}

void PlayerController::UpdateInput() {
    PawnController::UpdateInput();

    controlledPlayer = nullptr;
    controlledPlayer->childList;

    inputMovement = bn::fixed_point(0,0);

    if(bn::keypad::left_held())
    {
        inputMovement.set_x(-1);
    }
    else if(bn::keypad::right_held())
    {
        inputMovement.set_x(1);
    }
    if(bn::keypad::up_held())
    {
        inputMovement.set_y(-1);
    }
    else if(bn::keypad::down_held())
    {
        inputMovement.set_y(1);
    }

}

void PlayerController::Possess(Pawn* p) {
    PawnController::Possess(p);
    controlledPlayer = (Player*) controlledPawn;
}

void PlayerController:: Unpossess() {
    PawnController::Unpossess();
    controlledPlayer = (Player*) controlledPawn;
}