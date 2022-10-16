#include "Layer.h"

Layer::Layer() : GameObject::GameObject() {
    layerDepth = 0;
}

Layer::Layer(const int posX, const int posY, GameObject* _parent) : GameObject::GameObject(posX, posY, _parent){
    layerDepth = 0;
}

Layer::~Layer() {

}

void Layer::Start() {
    GameObject::Start();
}

void Layer::Update() {
    GameObject::Update();
    SetLocalPosition(camera->GetWorldPosition() * layerMovementAlpha);
}   

void Layer::Render() {
    GameObject::Render();
    if(back.has_value()) {
        back->set_position(GetScreenPosition());
    }
}

void Layer::SetLayerDepth(int depth) {
    layerDepth = depth;
    bn::fixed speed = 1;
    
    if(depth == -1) {
        depth = 0;
        if(back.has_value()) {
            back->set_z_order(0);
        }
        speed = -1.0f;
    }
    else {
        speed = 1 - 1.0f/(layerDepth+1);
    }
    if(back.has_value()) {
        back->set_priority(depth);
        back->set_z_order(3);
    }

    int size = childList.size();
    for(int i = 0; i < size; ++i) {
        childList[i]->SetLayerDepth(layerDepth);
    }
    
    layerMovementAlpha = speed;
}

void Layer::SetBackground(bn::regular_bg_ptr b, int layer) {
    back = b;
    SetLayerDepth(layer);
}

// bn::fixed_point Layer::GetScreenPosition() {
//     bn::fixed_point worldLocation = GameObject::GetWorldPosition();
//     if(camera != nullptr) {
//         worldLocation -= camera->GetWorldPosition() * layerMovementAlpha;
//     }
//     return worldLocation;
// }