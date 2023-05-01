#ifndef BF_ENEMY_BOSS_H
#define BF_ENEMY_BOSS_H

#include "GameObjects/Enemy.h"
#include "GameObjectComponents/ProjectileAttackAbility.h"
#include "GameObjectComponents/Animator.h"
#include "GameObjectComponents/PatrollerController.h"

class EnemyBoss : public Enemy {

public:
    EnemyBoss() = default;
    virtual ~EnemyBoss() = default;

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

    virtual void Die();

    void Jump();
    virtual void Attack();
    void Dash();

    void UpdateAnimationState();
    virtual void SetPlayer(Character* p);

    virtual void SetMapCollision(MapCollision* mc);

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    virtual void GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) override;
};

#endif