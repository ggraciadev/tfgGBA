#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "NestedGameObject.h"
#include "bn_sprite_text_generator.h"


class Scene {

public:
    Scene();
    virtual ~Scene();

protected:

    bn::optional<NestedGameObject> parentObject;
    bn::optional<NestedGameObject> object1;
    bn::optional<NestedGameObject> object2;

    bn::optional<bn::sprite_text_generator> text_generator;
    

public:

    virtual void Start();

    virtual void Update();
    

};

#endif