#ifndef BF_ACTOR_H
#define BF_ACTOR_H

#include "GameObject.h"
#include <bn_sprite_ptr.h>

class Actor : public GameObject {

public:
    Actor();
    Actor(const int posX, const int posY, GameObject* _parent = nullptr, const bn::fixed gravity = 0);

    virtual ~Actor();

protected:

    bn::optional<bn::sprite_ptr> sprite;
    bn::fixed_point inputMovement;
    bn::fixed_point velocity;
    bn::fixed currentMovementSpeed;
    bn::fixed gravityValue = 9.8f / 120.0f;
    bool isGrounded = false;

public:

    virtual void Start() override;
    virtual void Update() override;
    virtual void Render() override;

    void SetCurrentMovementSpeed(bn::fixed s) {currentMovementSpeed = s;}
    const bn::fixed GetCurrentMovementSpeed() {return currentMovementSpeed;}

    void SetSprite(bn::sprite_ptr s) {sprite = s;}
    void SetInputMovement(bn::fixed_point md) {inputMovement = md;}
    void SetInputMovementX(bn::fixed x) {inputMovement.set_x(x);}
    void SetInputMovementY(bn::fixed y) {inputMovement.set_y(y);}
    void SetInputMovement(bn::fixed x, bn::fixed y) {SetInputMovement(bn::fixed_point(x, y));}
    void SetVelocity(bn::fixed_point v) {velocity = v;}
    void SetVelocity(bn::fixed x, bn::fixed y) {SetVelocity(bn::fixed_point(x, y));}

    void AddImpulse(bn::fixed_point impulse);
    void AddImpulse(bn::fixed x, bn::fixed y) {AddImpulse(bn::fixed_point(x, y));}

    const bn::fixed_point GetInputMovement() { return inputMovement; }
    const bn::fixed_point GetVelocity() { return velocity; }
    void CalcVelocity();
    void CheckCollisions();

    virtual void SetLayerDepth(int depth) override;
    
    void SetGravityValue(bn::fixed g) { gravityValue = g; }
    const bn::fixed GetGravityValue() { return gravityValue; }

    void SetGrounded(bool g);


};

#endif