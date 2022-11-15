#ifndef BF_INPUT_COMPONENT_H
#define BF_INPUT_COMPONENT_H

#include "GameObjectComponents/GameObjectComponent.h"

#include <bn_fixed_point.h>

class Character;

class InputComponent : public GameObjectComponent{
public:
    
    InputComponent();
    virtual ~InputComponent();

protected:
    Character* character;
    bn::fixed_point inputMovement;

public:
    virtual void Start() override;
    virtual void Update() override;

    inline void SetCharacter(Character* c) { character= c;}

};

#endif