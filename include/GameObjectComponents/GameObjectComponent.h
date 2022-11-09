#ifndef BF_GAME_OBJECT_COMPONENT_H
#define BF_GAME_OBJECT_COMPONENT_H

#include "bn_core.h"
#include "bn_string.h"

class GameObject;

enum UpdateType { PHYSICS_UPDATE, LOGIC_UPDATE, RENDER };

class GameObjectComponent {
public:
    
    GameObjectComponent();
    void SetGameObject(GameObject* go) { gameObject = go; }
    virtual ~GameObjectComponent();


protected:
    GameObject* gameObject;
    UpdateType updateType = UpdateType::LOGIC_UPDATE;

public:
    virtual void Start() {}
    virtual void Update() {}

    UpdateType GetUpdateType() const { return updateType; }

    static bn::string<32> GetClassName() { return "GameObjectComponent"; }
};

#endif