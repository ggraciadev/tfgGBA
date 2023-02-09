#ifndef BF_INPUT_COMPONENT_H
#define BF_INPUT_COMPONENT_H

#include "GameObjectComponents/GameObjectComponent.h"

#include <bn_fixed_point.h>

class Player;

class InputComponent : public GameObjectComponent{
public:
    
    InputComponent() = default;
    virtual ~InputComponent() = default;

protected:
    Player* player;
    bn::fixed_point inputMovement;

public:
    virtual void Start() override;
    virtual void Update() override;

    inline void SetPlayer(Player* p) { player = p;}

};

#endif