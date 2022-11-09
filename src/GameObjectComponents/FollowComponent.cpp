#include "GameObjectComponents/FollowComponent.h"
#include "GameObjects/GameObject.h"

FollowComponent::FollowComponent() {

}

FollowComponent::~FollowComponent() {

}

void FollowComponent::Update() {
    if(followObject != nullptr) {
        gameObject->SetLocalPosition(followObject->GetWorldPosition() * alphaOffset);
    }
}