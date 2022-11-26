#ifndef BF_CHARACTER_H
#define BF_CHARACTER_H

#include "GameObjects/GameObject.h"
#include "GameObjectComponents/Animator.h"
#include "GameObjectComponents/MovementComponent.h"
#include "GameObjectComponents/InputComponent.h"
#include "GameObjectComponents/BoxCollision.h"

static const int COLLISION_OFFSET_X -13
#define COLLISION_OFFSET_Y -26
#define COLLISION_WIDTH 26
#define COLLISION_HEIGHT 52

#define JUMP_SPEED -4

class Character : public GameObject {
public:
    Character();
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);
    virtual ~Character() = default;

protected:

    MovementComponent movement;
    InputComponent input;
    BoxCollision boxCollision;
    Animator animator;
    

public:
    void Start();

    void SetMapCollision(MapCollision* mc);

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    void SetInputMovement(bn::fixed_point md);
    void SetInputMovementX(bn::fixed x);
    void SetInputMovementY(bn::fixed y);

    void Jump();

};

#endif