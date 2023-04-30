#ifndef BF_SCENE_H
#define BF_SCENE_H

#include "bn_vector.h"
#include "GameObjects/GameObject.h"
#include "GUI/GUIWidget.h"

class Scene {

public:
    Scene() = default;
    virtual ~Scene() = default;

protected:
    bn::vector <GameObject*, 32> gameObjects;
    bn::vector <GUIWidget*, 32> gameWidgets;
public:

    virtual void Start();

    virtual void Update();

    virtual void PhysicsUpdate();

    virtual void Render();
    
};

#endif