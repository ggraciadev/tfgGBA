#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "Character.h"
#include "Layer.h"

#include "bn_vector.h"
#include "Camera.h"
#include "Factory.h"

class Scene {

public:
    Scene();
    virtual ~Scene();

protected:
    Factory<Character> characterFactory;
    bn::vector<GameObject*, 1000> objects;
    int gameObjectListSize;
    //bn::optional<bn::regular_bg_ptr> back;
    //bn::optional<Camera> mainCamera;

public:

    virtual void Start();

    virtual void Update();

    virtual void Render();
    
};

#endif