#ifndef BF_ENEMY_H
#define BF_ENEMY_H

#include "GameObjects/Character.h"
#include "bn_random.h"

class Enemy : public Character {

public:
    Enemy() = default;
    ~Enemy() = default;

protected:

    //InputComponent input;
    //JumpAbility jumpAb; 
    //MeleeComboAbility<3> meleeComboAb;
    //Animator<2, 2> animator;

    Character* player;
    bn::random rand;
    int seed;

    virtual void SetupAnimations();
    virtual void SetupAttacks();

public:
    void Start();
    void Update();

    void Jump();
    virtual void Attack();
    void Dash();

    void UpdateAnimationState();

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    virtual void SetPlayer(Character* p) { player = p; }

    virtual void Die() override;

    virtual void GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) override;
};

#endif