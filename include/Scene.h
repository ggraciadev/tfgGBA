#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "GameObject.h"
#include "Layer.h"

#include "bn_vector.h"
#include "Camera.h"

class Scene {

public:
    Scene();
    virtual ~Scene();

protected:

    bn::vector<GameObject*, 16> gameObjectList;
    int gameObjectListSize;
    bn::optional<bn::regular_bg_ptr> back;
    Camera* mainCamera;

    Layer* foreGround;
    Layer* layer0;
    Layer* layer1;
    Layer* layer2;

public:

    virtual void Start();

    virtual void Update();

    virtual void Render();
    
};

#endif