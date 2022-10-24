#ifndef BF_GAME_OBJECT_COMPONENT_H
#define BF_GAME_OBJECT_COMPONENT_H

#include "bn_core.h"
#include "bn_string.h"

class GameObject;

class GameObjectComponent {
public:
    
    GameObjectComponent();
    void SetGameObject(GameObject* go) { gameObject = go; }
    virtual ~GameObjectComponent();


protected:
    GameObject* gameObject;

public:
    virtual void Start() {}
    virtual void Update();
    virtual void Render() {}
    virtual void PhysicsUpdate() {}

    static bn::string<32> GetClassName() { return "GameObjectComponent"; }
};

#endif