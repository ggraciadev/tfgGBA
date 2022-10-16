#ifndef BF_GAME_OBJECT_H
#define BF_GAME_OBJECT_H

#include "bn_core.h"
#include <bn_fixed_point.h>
#include <bn_optional.h>
#include "bn_vector.h"

class GameObject {

public:
    GameObject();
    GameObject(const int posX, const int posY, GameObject* _parent = nullptr);

    GameObject* parent;
    bn::vector<GameObject*, 16> childList;

    virtual ~GameObject();

protected:

    static int CURRENT_ID;

    bn::fixed_point relativePosition;
    GameObject* camera;
    int id;

public:

    void SetCamera(GameObject* cam) { camera = cam; }

    virtual void Start();
    virtual void Update();
    virtual void Render();

    bool HasParent();
    GameObject* GetParent();

    virtual bn::fixed_point GetRelativePosition() { return relativePosition; }
    virtual bn::fixed_point GetWorldPosition();
    virtual bn::fixed_point GetScreenPosition();

    void SetLocalPosition(const bn::fixed_point& pos);
    void SetLocalPosition(const int posX, const int posY);
    void AddLocalOffset(const bn::fixed_point& delta);
    void AddLocalOffset(const int deltaX, const int deltaY);

    void SetParent(GameObject* p);
    virtual void AddChild(GameObject* child);
    virtual void RemoveChild(GameObject* child);
    virtual void RemoveAllChilds();

    bool Equals(GameObject* other) {return id == other->id;}

};

#endif