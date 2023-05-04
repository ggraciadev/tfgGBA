#ifndef BF_ENEMY_H
#define BF_ENEMY_H

#include "GameObjects/Character.h"
#include "bn_random.h"

class Enemy : public Character {

public:
    Enemy() = default;
    virtual ~Enemy() = default;

protected:

    //InputComponent input;
    //JumpAbility jumpAb; 
    //MeleeComboAbility<3> meleeComboAb;
    //Animator<2, 2> animator;

    Character* player;
    bn::random rand;
    int seed;
    int room;

    virtual void SetupAnimations();
    virtual void SetupAttacks();

public:
    virtual void Start();
    virtual void Update();

    void Jump();
    virtual void Attack();
    void Dash();

    void UpdateAnimationState();

    virtual void SetLayerDepth(int depth);
    virtual void SetZOrder(char z_order);

    virtual void SetPlayer(Character* p) { player = p; }

    virtual void Die() override;

    inline void SetRoom(int roomIndex) { room = roomIndex;}
    inline int GetRoom() const { return room; }

    virtual bool GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) override;
};

#endif