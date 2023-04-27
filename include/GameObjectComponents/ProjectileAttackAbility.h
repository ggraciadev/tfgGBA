#ifndef BF_SINGLE_ATTACK_ABILITY_H
#define BF_SINGLE_ATTACK_ABILITY_H

#include "GameObjectComponents/AttackAbility.h"

class Character;

class ProjectileAttackAbility : public AttackAbility{
public:
    
    ProjectileAttackAbility() = default;
    virtual ~ProjectileAttackAbility() = default;

protected:

    AttackInfo attackInfo;

public:
    virtual bool UseAbility() override;
    virtual void Update() override;
    virtual void Start() override;
    

    void SetAttackInfo(const AttackInfo &info) { 
        attackInfo = info;
    }
    inline AttackInfo& GetAttackInfo() { return attackInfo; }

};

#endif