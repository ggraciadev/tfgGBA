#ifndef BF_CAMERA_H
#define BF_CAMERA_H

#include "GameObject.h"
#include "bn_camera_actions.h"
#include "FollowComponent.h"

class Camera : public GameObject {

public:
    Camera();
    virtual ~Camera();

protected:
    FollowComponent followComponent;

public:
    void Start();
    void SetFollowObject(GameObject* _followObject) { followComponent.SetFollowObject(_followObject); }

};

#endif