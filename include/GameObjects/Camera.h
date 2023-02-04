#ifndef BF_CAMERA_H
#define BF_CAMERA_H

#include "GameObjects/GameObject.h"
#include "bn_camera_actions.h"
#include "GameObjectComponents/FollowComponent.h"

class Camera : public GameObject {

public:
    Camera() = default;
    virtual ~Camera() = default;

protected:
    FollowComponent followComponent;

public:
    void Start();
    void SetFollowObject(GameObject* _followObject) { followComponent.SetFollowObject(_followObject); }

};

#endif