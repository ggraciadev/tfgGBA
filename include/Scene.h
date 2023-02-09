#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "GameObjects/Player.h"
#include "GameObjects/BackgroundElement.h"
#include "GameObjects/MapLayer.h"
#include "GameObjects/Camera.h"
#include "GameObjects/Layer.h"
#include "Factory.h"

#include <bn_regular_bg_ptr.h>
#include "bn_vector.h"

class Scene {

public:
    Scene();
    virtual ~Scene();

protected:
    Camera camera;
    MapLayer mapLayer;
    Layer<64,32> layer1;
    Layer<64,32> layer2;
    Factory<Player, 1> player;
    Factory<Character, 10> characterFactory;
    Factory<BackgroundElement<4,4>, 1> bg0ElementsFactory;
    Factory<BackgroundElement<2,2>, 2> bg1ElementsFactory;
    Factory<BackgroundElement<1,1>, 5> bg2ElementsFactory;
    bn::vector<GameObject*, 1000> objects;
    int gameObjectListSize;
    //bn::optional<bn::regular_bg_ptr> back;
    //bn::optional<Camera> mainCamera;

public:

    virtual void Start();

    virtual void Update();

    virtual void PhysicsUpdate();

    virtual void Render();
    
};

#endif