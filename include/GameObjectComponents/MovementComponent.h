#ifndef BF_MOVEMENT_COMPONENT_H
#define BF_MOVEMENT_COMPONENT_H

#include "GameObjectComponents/GameObjectComponent.h"
#include <bn_fixed_point.h>

#define MAX_VERTICAL_SPEED 10

class MovementComponent : public GameObjectComponent{
public:
    
    MovementComponent() = default;
    virtual ~MovementComponent() = default;

protected:
    bn::fixed_point inputMovement;
    bn::fixed_point velocity;
    bn::fixed currentMovementSpeed;
    bn::fixed gravityValue = 9.8f / (10*120.0f);
    int movementDirection;
    int currentImpulseDuration;
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

    void AddImpulse(bn::fixed_point impulse, int impulseDuration = 60);
    inline void AddImpulseForward(bn::fixed impulse, int impulseDuration = 60) {AddImpulse(bn::fixed_point(impulse * movementDirection, 0), impulseDuration);}
    inline void AddImpulseBackward(bn::fixed impulse, int impulseDuration = 60) {AddImpulse(bn::fixed_point(impulse * (-movementDirection), 0), impulseDuration);}
    inline void AddImpulseUp(bn::fixed impulse, int impulseDuration = 60) {AddImpulse(bn::fixed_point(0, -impulse), impulseDuration);}
    inline void AddImpulse(bn::fixed x, bn::fixed y, int impulseDuration = 60) { AddImpulse(bn::fixed_point(x, y), impulseDuration); }

    inline  bn::fixed_point GetInputMovement() const { return inputMovement; }
    inline bn::fixed_point GetVelocity() const { return velocity; }
    void CalcVelocity();
    void CheckCollisions() const;

    inline int GetMovementDirection() const { return movementDirection; }
    inline void SetMovementDirection(const int dir) { movementDirection = dir; }
    
    inline void SetGravityValue(bn::fixed g) { gravityValue = g; }
    inline bn::fixed GetGravityValue() const { return gravityValue; }

    void SetGrounded(bool g);
    inline bool IsGrounded() const { return isGrounded; }
};

#endif