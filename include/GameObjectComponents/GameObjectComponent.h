#ifndef BF_GAME_OBJECT_COMPONENT_H
#define BF_GAME_OBJECT_COMPONENT_H

#include "bn_core.h"
#include "bn_string.h"

class GameObject;

enum UpdateType { PHYSICS_UPDATE, LOGIC_UPDATE, RENDER };

class GameObjectComponent {
public:
    
    GameObjectComponent();
    inline void SetGameObject(GameObject* go) { gameObject = go; }
    virtual ~GameObjectComponent();


protected:
    GameObject* gameObject;
    UpdateType updateType = UpdateType::LOGIC_UPDATE;

public:
    virtual void Start() {}
    virtual void Update() {}

    inline UpdateType GetUpdateType() const { return updateType; }
};

#endif