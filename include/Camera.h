#ifndef BF_CAMERA_H
#define BF_CAMERA_H

#include "GameObject.h"
#include "Actor.h"
#include "bn_camera_actions.h"

class Camera : public GameObject {

public:
    Camera();
    Camera(const int posX, const int posY, GameObject* _parent = nullptr, Actor* follow = nullptr);
    virtual ~Camera();

protected:
    Actor* followActor;

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    virtual void SetFollowActor(Actor* _followActor);
    Actor* GetFollowActor() { return followActor; }

};

#endif