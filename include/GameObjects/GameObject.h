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
    ~GameObject();

protected:
    BN_DATA_EWRAM static int CURRENT_ID;

    GameObject* parent;
    bn::vector<GameObjectComponent*, MAX_COMPONENTS> components;

    struct Data {
        int id : 6;
        char layerDepth: 2;
        char zOrder : 4;
        char firtsLogicUpdateIndex : 3;
        char firstRenderIndex : 3;
        char componentsSize : 3;
        bool worldPositionDirty : 1;
    }  data;

    bn::fixed_point relativePosition;
    bn::fixed_point worldPosition;
    GameObject* camera;

private:
    void SortComponentsByUpdates();

public:

    inline void SetCamera(GameObject* cam) { camera = cam; }

    void Start();
    void PhysicsUpdate();
    void Update();
    void Render();

    inline const bn::fixed_point GetRelativePosition() const { return relativePosition; }
    bn::fixed_point GetWorldPosition() const;
    bn::fixed_point GetScreenPosition();

    void SetLocalPosition(const bn::fixed_point& pos);
    void SetLocalPosition(const int posX, const int posY);
    void AddLocalOffset(const bn::fixed_point& delta);
    void AddLocalOffset(const int deltaX, const int deltaY);

    void AddComponent(GameObjectComponent& component) {}
    void AddComponent(GameObjectComponent&& component) {}
    void AddComponent(GameObjectComponent* component);

    inline bool HasParent() const { return parent != nullptr; }
    inline GameObject* GetParent() const { return parent; }
    inline void SetParent(GameObject* p) { parent = p; }

    inline bool Equals(const GameObject& other) const {return data.id == other.data.id;}
    inline bool Equals(const GameObject* other) const {return data.id == other->data.id;}

    inline char GetLayerDepth() const { return data.layerDepth; }

    void SetLayerDepth(const int depth);
    inline void SetZOrder(const char z_order) { data.zOrder = z_order; }

    bool GetWorldPositionDirty();

};

#endif