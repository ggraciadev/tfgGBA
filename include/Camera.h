#ifndef BF_CAMERA_H
#define BF_CAMERA_H

#include "GameObject.h"
#include "bn_camera_actions.h"

class Camera : public GameObject {

public:
    Camera();
    virtual ~Camera();

protected:
    GameObject* followObject;

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    virtual void SetFollowObject(GameObject* _followObject);
    GameObject* GetFollowObject() { return followObject; }

};

#endif