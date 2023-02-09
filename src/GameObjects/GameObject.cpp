#include "GameObjects/GameObject.h"
#include "GameObjectComponents/GameObjectComponent.h"

int GameObject::CURRENT_ID = 0;

GameObject::GameObject()
    : relativePosition(0,0)
    , parent(nullptr)
    , camera(nullptr)
    , layerDepth(0)
{

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

    int size = components.size();
    for(int i = 0; i < size; ++i) {
        components[i]->SetGameObject(this);
        components[i]->Start();
    }
    componentsSize = components.size();
    SortComponentsByUpdates();
}

void GameObject::SortComponentsByUpdates() {
    bn::sort(components.begin(), components.end(), 
    [](auto i_left, auto i_right) { 
        return i_left->GetUpdateType() < i_right->GetUpdateType();
        });
    firtsLogicUpdateIndex = 0;
    firstRenderIndex = componentsSize;
    lastRenderIndex = componentsSize;
    bool passPh = false;
    bool passLogic = false;
    bool passRender = false;
    for(int i = 0; i < componentsSize; ++i) {
        if(!passRender && components[i]->GetUpdateType() == UpdateType::NO_UPDATE) {
            passPh = true;
            passLogic = true;
            passRender = true;
            lastRenderIndex = i;
        }
        else if(!passLogic && components[i]->GetUpdateType() == UpdateType::RENDER) {
            passPh = true;
            passLogic = true;
            firstRenderIndex = i;
        }
        else if(!passPh && components[i]->GetUpdateType() == UpdateType::LOGIC_UPDATE) {
            passPh = true;
            firtsLogicUpdateIndex = i;
        }
    }
}

void GameObject::PhysicsUpdate() {
    for(int i = 0; i < firtsLogicUpdateIndex; ++i) {
        components[i]->Update();
    }
}

void GameObject::Update() {
    for(int i = firtsLogicUpdateIndex; i < firstRenderIndex; ++i) {
        components[i]->Update();
    }
}

void GameObject::Render() {
    for(int i = firstRenderIndex; i < lastRenderIndex; ++i) {
        components[i]->Update();
    }
}

void GameObject::AddComponent(GameObjectComponent* component) {
    components.push_back(component);
}

bn::fixed_point GameObject::GetWorldPosition() const {
    bn::fixed_point worldLocation = relativePosition;
    if(parent != nullptr) {
        worldLocation += parent->GetWorldPosition();
    }
    return worldLocation;
}

bn::fixed_point GameObject::GetScreenPosition() const {
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

void GameObject::SetLayerDepth(const int depth) {
    if(depth == -1) {
        layerDepth = 0;
        SetZOrder(0);
    }
    else {
        layerDepth = depth;
    }

}

bool GameObject::GetWorldPositionDirty() {
    if(parent != nullptr) 
        worldPositionDirty = parent->GetWorldPositionDirty(); 
    return worldPositionDirty;
}