#include "GameObject.h"
#include "GameObjectComponent.h"

int GameObject::CURRENT_ID = 0;

GameObject::GameObject() {
    relativePosition = bn::fixed_point(0,0);
    //parent = nullptr;
    id = CURRENT_ID++;
}

// GameObject::GameObject(const int posX, const int posY, GameObject& _parent) {
//     relativePosition = bn::fixed_point(posX,  posY);
//     //parent = (_parent);
//     id = CURRENT_ID++;
//     componentsSize = 0;
//     components.clear();
// }

GameObject::~GameObject() {

}

void GameObject::Start() {

}

void GameObject::Update() {

}

void GameObject::Render() {
    
}

// bool GameObject::HasParent() {
//     return parent.has_value();
// }

// GameObject* GameObject::GetParent() {
//     return &(*parent);
// }

// void GameObject::SetParent(GameObject* p) {
//     //recalc local position 
//     parent = p;
//     if(parent != nullptr) {
//         (*parent).AddChild(this);
//     }
// }

// void GameObject::AddChild(GameObject* child) {
//     int size = childList.size();
//     for(int i = 0; i < size; ++i) {
//         if(childList[i]->Equals(child)) {
//             return;
//         }
//     }
//     childList.push_back(child);
// }

// void GameObject::RemoveChild(GameObject* child) {
//     int size = childList.size();
//     for(int i = 0; i < size; ++i) {
//         if(childList[i]->Equals(child)) {
//             //childList.erase(i);
//             return;
//         }
//     }
// }

// void GameObject::RemoveAllChilds() {
//     childList.clear();
// }

bn::fixed_point GameObject::GetWorldPosition() {
    bn::fixed_point worldLocation = relativePosition;
    // if(parent != nullptr) {
    //     worldLocation += parent->GetWorldPosition();
    // }
    return worldLocation;
}

bn::fixed_point GameObject::GetScreenPosition() {
    bn::fixed_point screenLocation = GetWorldPosition();
    // if(camera.has_value()) {
    //     screenLocation -= camera->GetWorldPosition();
    // }
    return screenLocation;
}

void GameObject::AddLocalOffset(const bn::fixed_point& delta) {
    relativePosition.set_x(relativePosition.x());
    relativePosition += delta;
}

void GameObject::AddLocalOffset(int deltaX, int deltaY) {
    AddLocalOffset(bn::fixed_point(deltaX, deltaY));
}

void GameObject::SetLocalPosition(const bn::fixed_point& pos) {
    relativePosition = pos;
}
void GameObject::SetLocalPosition(const int posX, const int posY) {
    AddLocalOffset(bn::fixed_point(posX, posY));
}