#include "PawnController.h"
#include "Pawn.h"

PawnController::PawnController() {

}

PawnController::~PawnController() {

}

void PawnController::Start() {
    inputMovement = bn::fixed_point(0,0);
}

void PawnController::Update() {
    UpdateInput();
    controlledPawn->SetInputMovement(inputMovement);
}

void PawnController::UpdateInput() {
    
}

void PawnController::Possess(Pawn* p) {
    if(p->GetController() == nullptr) {
        if(controlledPawn != nullptr) {
            controlledPawn->SetPawnController(nullptr);
        }
        controlledPawn = p;
        controlledPawn->SetPawnController(this);
    }
}

void PawnController::Unpossess() {
    if(controlledPawn != nullptr) {
        controlledPawn->SetPawnController(nullptr);
        controlledPawn = nullptr;
    }
}