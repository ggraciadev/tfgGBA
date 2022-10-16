#ifndef BF_NESTED_GAME_OBJECT_H
#define BF_NESTED_GAME_OBJECT_H

#include "GameObject.h"
#include "bn_vector.h"

#include <bn_sprite_ptr.h>

class NestedGameObject : public GameObject {

public:
    NestedGameObject();
    NestedGameObject(int posX, int posY);
    NestedGameObject(int posX, int posY, GameObject* _parent);
    virtual ~NestedGameObject();

protected:

    GameObject* parent;
    bn::vector<GameObject*, 16> childList;

    bn::optional<bn::sprite_ptr> sprite;


public:

    virtual void Start() override;
    virtual void Update() override;    

    void SetSprite(bn::optional<bn::sprite_ptr> s) { sprite = s; }

    bool HasParent();
    GameObject* GetParent();

    virtual bn::fixed_point GetWorldPosition() override;

    void AddLocalOffset(bn::fixed_point delta);
    void AddLocalOffset(int deltaX, int deltaY);

    void SetParent(GameObject* p);
    virtual void AddChild(GameObject* child) override;
    virtual void RemoveChild(GameObject* child) override;
    virtual void RemoveAllChilds() override;

};

#endif