#ifndef BF_GAME_OBJECT_H
#define BF_GAME_OBJECT_H

#include "bn_core.h"
#include <bn_fixed_point.h>
#include <bn_optional.h>
#include "bn_vector.h"
#include "GameObjectComponent.h"
#include "bn_string.h"

#define MAX_CHILDS 16
#define MAX_COMPONENTS 8

//class GameObjectComponent;

class GameObject {

public:
    GameObject();
    //GameObject(const int posX, const int posY, GameObject& _parent);
    virtual ~GameObject();

protected:
    BN_DATA_EWRAM static int CURRENT_ID;

    GameObject* parent;
    bn::vector<GameObjectComponent*, MAX_COMPONENTS> components;

    bn::fixed_point relativePosition;
    int id;

public:

    // void SetCamera(GameObject& cam) { camera = cam; }

    virtual void Start();
    virtual void Update();
    virtual void Render();

    // bool HasParent();
    // GameObject& GetParent();

    bn::fixed_point GetRelativePosition() { return relativePosition; }
    virtual bn::fixed_point GetWorldPosition();
    virtual bn::fixed_point GetScreenPosition();

    virtual void SetLayerDepth(int depth) { };

    void SetLocalPosition(const bn::fixed_point& pos);
    void SetLocalPosition(const int posX, const int posY);
    void AddLocalOffset(const bn::fixed_point& delta);
    void AddLocalOffset(const int deltaX, const int deltaY);

    void AddComponent(GameObjectComponent* component);

    // void SetParent(GameObject& p);
    // void AddChild(GameObject& child);
    // void RemoveChild(GameObject& child);
    // void RemoveAllChilds();

    bool Equals(GameObject& other) {return id == other.id;}

};

#endif