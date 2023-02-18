#ifndef BF_ENEMY_H
#define BF_ENEMY_H

#include "GameObjects/Character.h"
#include "GameObjectComponents/Animator.h"

class Enemy : public Character {

public:
    Enemy() = default;
    ~Enemy() = default;

protected:

    //InputComponent input;
    //JumpAbility jumpAb; 
    //MeleeComboAbility<3> meleeComboAb;
    Animator<2, 2> animator;

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

    virtual void GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) override;
};

#endif