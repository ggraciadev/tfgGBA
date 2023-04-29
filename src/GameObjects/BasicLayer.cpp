#include "GameObjects/BasicLayer.h"


void BasicLayer::SetBackgroundGraphic(const bn::regular_bg_item& bgItem) {
    background = bgItem.create_bg(0, 0);
}

void BasicLayer::Start() {
    followComponent.SetFollowObject(camera);
    AddComponent(&followComponent);
    

    GameObject::Start();
}

void BasicLayer::Update() {
    GameObject::Update();
}

void BasicLayer::SetLayerDepth(int depth) {
    bn::fixed speed = 1;
    
    GameObject::SetLayerDepth(depth);
    if(layerDepth == -1) {
        speed = -1.0f;
    }
    else if(layerDepth == 0) {
        speed = 0;
    }
    else if(layerDepth == 3) {
        speed = 1;
    }
    else {
        speed = 1 - 1.0f/((1+layerDepth)*2);
        SetZOrder(3);
    }
    followComponent.SetAlphaOffset(speed);
    background->set_priority(layerDepth);
    
}

char BasicLayer::GetBackgroundLayer() {
    return layerDepth;
}

void BasicLayer::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    background->set_z_order(z_order);
}

void BasicLayer::Render() {
    if(background.has_value()) {
        background->set_position(GetScreenPosition());
    }
}