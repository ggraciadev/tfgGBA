#ifndef BF_MOVEMENT_COMPONENT_H
#define BF_MOVEMENT_COMPONENT_H

#include "GameObjectComponents/GameObjectComponent.h"
#include <bn_fixed_point.h>


class MovementComponent : public GameObjectComponent{
public:
    
    MovementComponent();
    virtual ~MovementComponent();


protected:
    bn::fixed_point inputMovement;
    bn::fixed_point velocity;
    bn::fixed currentMovementSpeed;
    bn::fixed gravityValue = 9.8f / (10*120.0f);
    bool isGrounded = false;

public:
    virtual void Start() override;
    virtual void Update() override;

    inline void SetCurrentMovementSpeed(bn::fixed s) {currentMovementSpeed = s;}
    inline bn::fixed GetCurrentMovementSpeed() const {return currentMovementSpeed;}

    inline void SetInputMovement(bn::fixed_point md) {inputMovement = md;}
    inline void SetInputMovementX(bn::fixed x) {inputMovement.set_x(x);}
    inline void SetInputMovementY(bn::fixed y) {inputMovement.set_y(y);}

    inline void SetVelocityX(bn::fixed x) { velocity.set_x(x);}
    inline void SetVelocityY(bn::fixed y) { velocity.set_y(y);}
    //void SetInputMovement(bn::fixed x, bn::fixed y) {SetInputMovement(bn::fixed_point(x, y));}
    //void SetVelocity(bn::fixed_point v) {velocity = v;}
    //void SetVelocity(bn::fixed x, bn::fixed y) {SetVelocity(bn::fixed_point(x, y));}

    void AddImpulse(bn::fixed_point impulse);
    inline void AddImpulse(bn::fixed x, bn::fixed y) { AddImpulse(bn::fixed_point(x, y)); }

    inline  bn::fixed_point GetInputMovement() const { return inputMovement; }
    inline bn::fixed_point GetVelocity() const { return velocity; }
    void CalcVelocity();
    void CheckCollisions() const;
    
    inline void SetGravityValue(bn::fixed g) { gravityValue = g; }
    inline bn::fixed GetGravityValue() const { return gravityValue; }

    void SetGrounded(bool g);
};

#endif