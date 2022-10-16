#ifndef BF_GAME_OBJECT_H
#define BF_GAME_OBJECT_H

#include "bn_core.h"
#include <bn_fixed_point.h>
#include <bn_optional.h>

class GameObject {

public:
    GameObject();
    GameObject(int posX, int posY);
    virtual ~GameObject();

protected:

    bn::fixed_point relativePosition;
    int id;

public:

    virtual void Start() {}
    virtual void Update() {}

    bool HasParent() { return false; }
    virtual GameObject* GetParent() { return nullptr; }

    virtual bn::fixed_point GetWorldPosition() { return relativePosition; }
    bn::fixed_point GetRelativePosition() { return relativePosition; }

    virtual void AddChild(GameObject* go) {}
    virtual void RemoveChild(GameObject* child) {}
    virtual void RemoveAllChilds() {}
    bool Equals(GameObject* go) { return id == go->id; }

};

#endif