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

    int size = components.size();
    for(int i = 0; i < size; ++i) {
        components[i]->SetGameObject(this);
        components[i]->Start();
    }
    componentsSize = components.size();
    SortComponentsRender();
}

void GameObject::SortComponentsRender() {
    int i, j;
    for(i = 0; i < componentsSize-1; ++i) {
        bool swapped = false;
        for(j = 0; j < componentsSize-i-1; ++j) {
            if(components[j]->GetUpdateType() > components[j+1]->GetUpdateType()) {
                SwapComponents(components[j], components[j+1]);
                swapped = true;
            }
        }
        if(!swapped) {
            break;
        }
    }
    firtsLogicUpdateIndex = 0;
    firstRenderIndex = componentsSize;
    bool passPh = false;
    bool passLogic = false;
    for(i = 0; i < componentsSize; ++i) {
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
    for(int i = firstRenderIndex; i < componentsSize; ++i) {
        components[i]->Update();
    }
}

void GameObject::AddComponent(GameObjectComponent* component) {
    components.push_back(component);
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

void GameObject::SetLayerDepth(const int depth) {
    if(depth == -1) {
        layerDepth = 0;
        SetZOrder(0);
    }
    else {
        layerDepth = depth;
    }

}