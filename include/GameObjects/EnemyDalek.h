#ifndef BF_ENEMY_DALEK_H
#define BF_ENEMY_DALEK_H

#include "GameObjects/Enemy.h"
#include "GameObjectComponents/ProjectileAttackAbility.h"
#include "GameObjectComponents/Animator.h"
#include "GameObjectComponents/PatrollerController.h"

class EnemyDalek : public Enemy {

public:
    EnemyDalek() = default;
    virtual ~EnemyDalek() = default;

protected:

    //InputComponent input;
    //JumpAbility jumpAb; 
    PatrollerController patrollerController;
    ProjectileAttackAbility laserAttackAb;
    Animator<3, 8> animator;

    virtual void SetupAnimations();
    virtual void SetupAttacks();

public:
    virtual void Start();
    virtual void Update();

    void Jump();
    virtual void Attack();
    void Dash();

    void UpdateAnimationState();
    virtual void SetPlayer(Character* p);
    virtual void Die();

    virtual void SetMapCollision(MapCollision* mc);

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    virtual bool GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) override;
};

#endif