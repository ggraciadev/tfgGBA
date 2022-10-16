#include "NestedGameObject.h"



NestedGameObject::NestedGameObject() {
    relativePosition = bn::fixed_point(0,0);
    parent = nullptr;
}

NestedGameObject::NestedGameObject(int posX, int posY) {
    relativePosition = bn::fixed_point(posX,  posY);
    parent = nullptr;
}

NestedGameObject::NestedGameObject(int posX, int posY, GameObject* _parent) {
    relativePosition = bn::fixed_point(posX,  posY);
    parent = _parent;
}

NestedGameObject::~NestedGameObject() {

}

void NestedGameObject::Start() {

}

void NestedGameObject::Update() {
    (*sprite).set_position(GetWorldPosition());
}

bool NestedGameObject::HasParent() {
    return parent != nullptr;
}

GameObject* NestedGameObject::GetParent() {
    if(parent != nullptr) {
        return nullptr;
    }
    else {
        return &(*parent);
    }

}

void NestedGameObject::SetParent(GameObject* p) {
    //recalc local position 
    parent = p;
    (*parent).AddChild(this);
}

void NestedGameObject::AddChild(GameObject* child) {
    int size = childList.size();
    for(int i = 0; i < size; ++i) {
        if(childList[i]->Equals(child)) {
            return;
        }
    }
    childList.push_back(child);
}

void NestedGameObject::RemoveChild(GameObject* child) {
    int size = childList.size();
    for(int i = 0; i < size; ++i) {
        if(childList[i]->Equals(child)) {
            //childList.erase(i);
            return;
        }
    }
}

void NestedGameObject::RemoveAllChilds() {
    childList.clear();
}

bn::fixed_point NestedGameObject::GetWorldPosition() {
    bn::fixed_point worldLocation = relativePosition;
    if(parent != nullptr) {
        worldLocation += parent->GetWorldPosition();
    }
    return worldLocation;
}

void NestedGameObject::AddLocalOffset(bn::fixed_point delta) {
    relativePosition += delta;
}

void NestedGameObject::AddLocalOffset(int deltaX, int deltaY) {
    AddLocalOffset(bn::fixed_point(deltaX, deltaY));
}