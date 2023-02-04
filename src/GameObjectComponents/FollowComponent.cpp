#include "GameObjectComponents/FollowComponent.h"
#include "GameObjects/GameObject.h"

void FollowComponent::Update() {
    if(followObject != nullptr) {
        gameObject->SetLocalPosition(followObject->GetWorldPosition() * alphaOffset);
        //gameObject->AddLocalOffset(bn::fixed_point(0.001f, 0));
    }
}