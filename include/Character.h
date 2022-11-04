#ifndef BF_CHARACTER_H
#define BF_CHARACTER_H

#include "GameObject.h"
#include "Animator.h"
#include "MovementComponent.h"
#include "InputComponent.h"
#include "BoxCollision.h"


#define COLLISION_OFFSET_X -13
#define COLLISION_OFFSET_Y -26
#define COLLISION_WIDTH 26
#define COLLISION_HEIGHT 52

#define JUMP_SPEED -4

class Character : public GameObject {
public:
    Character();
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);
    virtual ~Character();

protected:

    MovementComponent movement;
    InputComponent input;
    BoxCollision boxCollision;
    Animator animator;
    

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void PhysicsUpdate() override;
    virtual void Render() override;

    virtual void SetMapCollision(MapCollision* mc);

    virtual void SetLayerDepth(int depth) override;
    virtual void SetZOrder(char z_order) override;

    void SetInputMovement(bn::fixed_point md);
    void SetInputMovementX(bn::fixed x);
    void SetInputMovementY(bn::fixed y);

    void Jump();

};

#endif