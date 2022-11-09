#ifndef BF_GAME_OBJECT_H
#define BF_GAME_OBJECT_H

#include "bn_core.h"
#include <bn_fixed_point.h>
#include <bn_optional.h>
#include "bn_vector.h"
#include "GameObjectComponent.h"
#include "bn_string.h"
#include <bn_sprite_item.h>

#define MAX_COMPONENTS 8

//class GameObjectComponent;

class MapCollision;

class GameObject {

public:
    GameObject();
    //GameObject(const int posX, const int posY, GameObject& _parent);
    ~GameObject();

protected:
    BN_DATA_EWRAM static int CURRENT_ID;

    GameObject* parent;
    bn::vector<GameObjectComponent*, MAX_COMPONENTS> components;

    bn::fixed_point relativePosition;
    bn::fixed_point worldPosition;
    bool worldPositionDirty;
    int id;

    char layerDepth;
    char zOrder;

    char firtsLogicUpdateIndex;
    char firstRenderIndex;
    char componentsSize;
    GameObject* camera;

public:

    void SetCamera(GameObject* cam) { camera = cam; }

    void Start();
    void PhysicsUpdate();
    void Update();
    void Render();

    void SwapComponents(GameObjectComponent* c1, GameObjectComponent* c2) { 
        GameObjectComponent* t = c1; 
        c1 = c2; 
        c2 = t;
    }
    void SortComponentsRender();

    const bn::fixed_point GetRelativePosition() { return relativePosition; }
    bn::fixed_point GetWorldPosition();
    bn::fixed_point GetScreenPosition();

    void SetLocalPosition(const bn::fixed_point& pos);
    void SetLocalPosition(const int posX, const int posY);
    void AddLocalOffset(const bn::fixed_point& delta);
    void AddLocalOffset(const int deltaX, const int deltaY);

    void AddComponent(GameObjectComponent* component);

    bool HasParent() const { return parent != nullptr; }
    GameObject* GetParent() const { return parent; }
    void SetParent(GameObject* p) { parent = p; }

    bool Equals(const GameObject& other) const {return id == other.id;}
    bool Equals(const GameObject* other) const {return id == other->id;}

    char GetLayerDepth() const { return layerDepth; }

    void SetLayerDepth(const int depth);
    void SetZOrder(const char z_order) { zOrder = z_order; }

    bool GetWorldPositionDirty() {if(parent != nullptr) worldPositionDirty = parent->GetWorldPositionDirty(); return worldPositionDirty;}

};

#endif