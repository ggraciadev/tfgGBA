#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "Character.h"
#include "Layer.h"
#include <bn_regular_bg_ptr.h>

#include "bn_vector.h"
#include "Camera.h"
#include "Layer.h"
#include "Factory.h"

class Scene {

public:
    Scene();
    virtual ~Scene();

protected:
    Camera camera;
    Layer<64,32> layer;
    Layer<64,32> layer1;
    Layer<64,32> layer2;
    Factory<Character, 10> characterFactory;
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