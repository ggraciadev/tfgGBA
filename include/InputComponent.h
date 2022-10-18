#ifndef BF_INPUT_COMPONENT_H
#define BF_INPUT_COMPONENT_H

#include "MovementComponent.h"
#include <bn_fixed_point.h>

class InputComponent : public GameObjectComponent{
public:
    
    InputComponent();
    virtual ~InputComponent();

protected:
    MovementComponent* movementComponent;
    bn::fixed_point inputMovement;

public:
    virtual void Start() override;
    virtual void Update() override;

    void SetMovementComponent(MovementComponent* mC) { movementComponent = mC;}

};

#endif