#ifndef BF_GAME_OBJECT_H
#define BF_GAME_OBJECT_H

#include "bn_core.h"
#include <bn_fixed_point.h>
#include <bn_optional.h>
#include "bn_vector.h"
#include "GameObjectComponents/GameObjectComponent.h"
#include "bn_string.h"
#include <bn_sprite_item.h>

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
    bn::vector<GameObjectComponent*, MAX_COMPONENTS> components;
    
    bn::fixed_point relativePosition;

    GameObject* parent;
    GameObject* camera;

    int id;

    char layerDepth;
    char zOrder;

    char firtsLogicUpdateIndex;
    char firstRenderIndex;
    char lastRenderIndex;
    char componentsSize;

    bool destroyed;

private:
    void SortComponentsByUpdates();

public:

    virtual void SetCamera(GameObject* cam) { camera = cam; }
    virtual void Init();
    virtual void Start();
    virtual void PhysicsUpdate();
    virtual void Update();
    virtual void Render();
    void Destroy() { destroyed = true; }
    void SetDestroyed(bool d) { destroyed = true; }
    bool GetDestroyed() { return destroyed; }

    inline const bn::fixed_point GetRelativePosition() { return relativePosition; }
    bn::fixed_point GetWorldPosition() const;
    bn::fixed_point GetScreenPosition() const;

    void SetLocalPosition(const bn::fixed_point& pos);
    void SetLocalPosition(const int posX, const int posY);
    void AddLocalOffset(const bn::fixed_point& delta);
    void AddLocalOffset(const int deltaX, const int deltaY);

    void AddComponent(GameObjectComponent* component);

    inline bool HasParent() const { return parent != nullptr; }
    inline GameObject* GetParent() const { return parent; }
    inline void SetParent(GameObject* p) { parent = p; }

    inline bool Equals(const GameObject& other) const {return id == other.id;}
    inline bool Equals(const GameObject* other) const {return id == other->id;}

    inline char GetLayerDepth() const { return layerDepth; }

    virtual void SetLayerDepth(const int depth);
    virtual void SetZOrder(const char z_order) { zOrder = z_order; }


};

#endif