#ifndef BF_GAME_OBJECT_H
#define BF_GAME_OBJECT_H

#include "bn_core.h"
#include <bn_fixed_point.h>
#include <bn_optional.h>
#include "bn_vector.h"
#include "GameObjectComponent.h"
#include "bn_string.h"

#define MAX_COMPONENTS 8

//class GameObjectComponent;

class MapCollision;

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

    char layerDepth;
    char zOrder;

    GameObject* camera;

public:

    void SetCamera(GameObject* cam) { camera = cam; }

    virtual void Start();
    virtual void Update();
    virtual void PhysicsUpdate();
    virtual void Render();

    virtual void SetMapCollision(MapCollision* mc) {}

    bn::fixed_point GetRelativePosition() { return relativePosition; }
    virtual bn::fixed_point GetWorldPosition();
    virtual bn::fixed_point GetScreenPosition();

    void SetLocalPosition(const bn::fixed_point& pos);
    void SetLocalPosition(const int posX, const int posY);
    void AddLocalOffset(const bn::fixed_point& delta);
    void AddLocalOffset(const int deltaX, const int deltaY);

    void AddComponent(GameObjectComponent* component);

    bool HasParent();
    GameObject* GetParent();
    void SetParent(GameObject* p);

    bool Equals(GameObject& other) {return id == other.id;}
    bool Equals(GameObject* other) {return id == other->id;}

    char GetLayerDepth() { return layerDepth; }
    void UpdateLayer();

    virtual char GetBackgroundLayer();
    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    virtual void OnCollisionEnter(GameObject* other) {}
    virtual void OnCollisionStay(GameObject* other) {}
    virtual void OnCollisionExit(GameObject* other) {}

    virtual void OnTriggerEnter(GameObject* other) {}
    virtual void OnTriggerStay(GameObject* other) {}
    virtual void OnTriggerExit(GameObject* other) {}

};

#endif