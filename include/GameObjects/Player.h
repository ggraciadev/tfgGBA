#ifndef BF_PLAYER_H
#define BF_PLAYER_H

#include "GameObjects/Character.h"
#include "GameObjectComponents/Animator.h"
#include "GameObjectComponents/InputComponent.h"
#include "GameObjectComponents/JumpAbility.h"
#include "GameObjectComponents/MeleeComboAbility.h"

class Player : public Character {

public:
    Player() = default;
    ~Player() = default;

protected:

    InputComponent input;
    JumpAbility jumpAb; 
    MeleeComboAbility<3> meleeComboAb;
    Animator<4, 16> animator;

    virtual void SetupAnimations();
    virtual void SetupAttacks();

public:
    void Start();
    void Update();

    void Jump();
    void Attack();
    void Dash();

    void UpdateAnimationState();

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    virtual void GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition);
};

#endif