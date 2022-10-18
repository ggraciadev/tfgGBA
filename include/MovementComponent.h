#ifndef BF_MOVEMENT_COMPONENT_H
#define BF_MOVEMENT_COMPONENT_H

#include "GameObjectComponent.h"
#include <bn_fixed_point.h>


class MovementComponent : public GameObjectComponent{
public:
    
    MovementComponent();
    virtual ~MovementComponent();


protected:
    bn::fixed_point inputMovement;
    bn::fixed_point velocity;
    bn::fixed currentMovementSpeed;
    bn::fixed gravityValue = 9.8f / 120.0f;
    bool isGrounded = false;

public:
    virtual void Start() override;
    virtual void Update() override;

    void SetCurrentMovementSpeed(bn::fixed s) {currentMovementSpeed = s;}
    const bn::fixed GetCurrentMovementSpeed() {return currentMovementSpeed;}

    void SetInputMovement(bn::fixed_point md) {inputMovement = md;}
    void SetInputMovementX(bn::fixed x) {inputMovement.set_x(x);}
    void SetInputMovementY(bn::fixed y) {inputMovement.set_y(y);}
    //void SetInputMovement(bn::fixed x, bn::fixed y) {SetInputMovement(bn::fixed_point(x, y));}
    //void SetVelocity(bn::fixed_point v) {velocity = v;}
    //void SetVelocity(bn::fixed x, bn::fixed y) {SetVelocity(bn::fixed_point(x, y));}

    //void AddImpulse(bn::fixed_point impulse);
    //void AddImpulse(bn::fixed x, bn::fixed y) {AddImpulse(bn::fixed_point(x, y));}

    const bn::fixed_point GetInputMovement() { return inputMovement; }
    const bn::fixed_point GetVelocity() { return velocity; }
    void CalcVelocity();
    void CheckCollisions();
    
    void SetGravityValue(bn::fixed g) { gravityValue = g; }
    const bn::fixed GetGravityValue() { return gravityValue; }

    void SetGrounded(bool g);

    static bn::string<32> GetClassName() { return "MovementComponent"; }
};

#endif