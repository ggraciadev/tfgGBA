#include "Pawn.h"
#include "PawnController.h"

Pawn::Pawn() : Actor::Actor() {
    controller = nullptr;
}

Pawn::Pawn(const int posX, const int posY, GameObject* _parent, const bn::fixed gravity) : Actor::Actor(posX, posY, _parent, gravity){
    controller = nullptr;
}

Pawn::~Pawn() {

}

void Pawn::Start() {
    Actor::Start();
}
void Pawn::Update() {
    if(controller != nullptr) {
        controller->Update();
        Actor::Update();
    }
}

void Pawn::SetPawnController(PawnController* pc) {
    controller = pc;
}