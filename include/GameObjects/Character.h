#ifndef BF_CHARACTER_H
#define BF_CHARACTER_H

#include "GameObjects/GameObject.h"
#include "GameObjectComponents/MovementComponent.h"
#include "GameObjectComponents/BoxCollision.h"
#include "GameObjectComponents/JumpAbility.h"
#include "GameObjectComponents/DamageRecieverAbility.h"


#define COLLISION_OFFSET_X -13
#define COLLISION_OFFSET_Y -26
#define COLLISION_WIDTH 26
#define COLLISION_HEIGHT 52
#define MOVEMENT_SPEED 1.5
#define JUMP_SPEED -4
#define MAX_JUMPS 2
#define COOLDOWN_COMBO 20

struct CharacterInfo {
    BoxExtension boxCollisionExtension;
    bn::fixed movementSpeed;
    int jumpSpeed;

    CharacterInfo() {
        boxCollisionExtension = BoxExtension(bn::fixed_point(COLLISION_OFFSET_X, COLLISION_OFFSET_Y), bn::fixed_point(COLLISION_WIDTH, COLLISION_HEIGHT));
        movementSpeed = MOVEMENT_SPEED;
        jumpSpeed = JUMP_SPEED;
    };
};
class Attack;

class Character : public GameObject {
public:
    Character() = default;
    ~Character() = default;
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);

protected:

    MovementComponent movement;
    BoxCollision boxCollision;
    DamageRecieverAbility damageReciever;

    CharacterInfo characterInfo;

    void SetupAnimations() {};
    void SetupAttacks() {};

public:
    void Start();

    void SetMapCollision(MapCollision* mc);

    void SetLayerDepth(int depth);

    void SetInputMovement(bn::fixed_point md);
    void SetInputMovementX(bn::fixed x);
    void SetInputMovementY(bn::fixed y);

    inline MovementComponent* GetMovementComponent() { return &movement; }

    void UpdateAnimationState();

    virtual void GetDamage(const AttackInfo& atkInfo);
    BoxCollision* GetBoxCollision();

};

#endif