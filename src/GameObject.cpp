#include "GameObject.h"
#include "GameObjectComponent.h"

int GameObject::CURRENT_ID = 0;

GameObject::GameObject() {
    relativePosition = bn::fixed_point(0,0);
    parent = nullptr;
    camera = nullptr;
    layerDepth = 0;
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
    id = CURRENT_ID++;

    UpdateLayer();

    int size = components.size();
    for(int i = 0; i < size; ++i) {
        components[i]->SetGameObject(this);
        components[i]->Start();
    }
}

void GameObject::Update() {
    int size = components.size();
    for(int i = 0; i < size; ++i) {
        components[i]->Update();
    }
}

void GameObject::PhysicsUpdate() {
    
}

void GameObject::Render() {
}

void GameObject::AddComponent(GameObjectComponent* component) {
    components.push_back(component);
}

bool GameObject::HasParent() {
    return parent != nullptr;
}

GameObject* GameObject::GetParent() {
    return parent;
}

void GameObject::SetParent(GameObject* p) {
    //recalc local position 
    parent = p;
}

bn::fixed_point GameObject::GetWorldPosition() {
    bn::fixed_point worldLocation = relativePosition;
    if(parent != nullptr) {
        worldLocation += parent->GetWorldPosition();
    }
    return worldLocation;
}

bn::fixed_point GameObject::GetScreenPosition() {
    bn::fixed_point screenLocation = GetWorldPosition();
    if(camera != nullptr) {
        screenLocation -= camera->GetWorldPosition();
    }
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

char GameObject::GetBackgroundLayer() {
    if(parent == nullptr) {
        return 0;
    }
    else {
        return parent->GetBackgroundLayer();
    }
}

void GameObject::SetLayerDepth(int depth) {
    if(depth == -1) {
        depth = 0;
        SetZOrder(0);
    }

    layerDepth = depth;
}

void GameObject::UpdateLayer() {
    SetLayerDepth(GetBackgroundLayer());
}

void GameObject::SetZOrder(char z_order) {

}