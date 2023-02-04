#include "GameObjects/GameObject.h"
#include "GameObjectComponents/GameObjectComponent.h"

int GameObject::CURRENT_ID = 0;

GameObject::GameObject()
    : relativePosition(0,0)
    , parent(nullptr)
    , camera(nullptr)
    , data()
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
    data.id = CURRENT_ID++;

    int size = components.size();
    for(auto& element : components) 
    {
        element->SetGameObject(this);
        element->Start();
    }
    data.componentsSize = components.size();
    SortComponentsByUpdates();
}

void GameObject::SortComponentsByUpdates() {
    bn::sort(components.begin(), components.end(), 
    [](auto i_left, auto i_right) { 
        return i_left->GetUpdateType() < i_right->GetUpdateType();
        });
    int firtsLogicUpdateIndex = 0;
    int firstRenderIndex = data.componentsSize;
    bool passPh = false;
    bool passLogic = false;
    for(int i = 0; i < data.componentsSize; ++i) {
        if(!passLogic && components[i]->GetUpdateType() == UpdateType::RENDER) {
            passPh = true;
            passLogic = true;
            firstRenderIndex = i;
            break;
        }
        else if(!passPh && components[i]->GetUpdateType() == UpdateType::LOGIC_UPDATE) {
            passPh = true;
            firtsLogicUpdateIndex = i;
        }
    }
}

void GameObject::PhysicsUpdate() {
    for(int i = 0; i < data.firtsLogicUpdateIndex; ++i) {
        components[i]->Update();
    }
}

void GameObject::Update() {
    for(int i = data.firtsLogicUpdateIndex; i < data.firstRenderIndex; ++i) {
        components[i]->Update();
    }
}

void GameObject::Render() {
    for(int i = data.firstRenderIndex; i < data.componentsSize; ++i) {
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

bn::fixed_point GameObject::GetScreenPosition() {
    bn::fixed_point screenLocation = GetWorldPosition();
    if(camera != nullptr) {
        screenLocation -= camera->GetWorldPosition();
    }
    return screenLocation;
}

void GameObject::AddLocalOffset(const bn::fixed_point& delta) {
    relativePosition += delta;
}

void GameObject::AddLocalOffset(int deltaX, int deltaY) {
    AddLocalOffset(bn::fixed_point(deltaX, deltaY));
}

void GameObject::SetLocalPosition(const bn::fixed_point& pos) {
    relativePosition = pos;
}
void GameObject::SetLocalPosition(const int posX, const int posY) {
    relativePosition.set_x(posX);
    relativePosition.set_y(posY);
}

void GameObject::SetLayerDepth(const int depth) {
    if(depth == -1) {
        data.layerDepth = 0;
        SetZOrder(0);
    }
    else {
        data.layerDepth = depth;
    }

}

bool GameObject::GetWorldPositionDirty() {
    if(parent != nullptr) {
        data.worldPositionDirty = data.worldPositionDirty && parent->GetWorldPositionDirty(); 
    }
    return data.worldPositionDirty;
}