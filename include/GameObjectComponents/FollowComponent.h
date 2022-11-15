#ifndef BF_FOLLOW_COMPONENT_H
#define BF_FOLLOW_COMPONENT_H

#include "GameObjectComponents/GameObjectComponent.h"
#include <bn_fixed_point.h>


class FollowComponent : public GameObjectComponent{
public:
    
    FollowComponent();
    virtual ~FollowComponent();

protected:

    GameObject* followObject;

    bn::fixed alphaOffset = 1;

public:

    inline void SetFollowObject(GameObject* _followObject) { followObject = _followObject; }
    //virtual void Start() override {}
    virtual void Update() override;

    inline void SetAlphaOffset(const bn::fixed& ao) { alphaOffset = ao;}
};

#endif