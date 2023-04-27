#include "AIController.h"

void AIController::Start() {
    updateType = UpdateType::PHYSICS_UPDATE;
    GameObjectComponent::Start();
}

void AIController::Update() {
    GameObjectComponent::Update();
}