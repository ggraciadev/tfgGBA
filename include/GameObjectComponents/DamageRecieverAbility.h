#ifndef BF_DAMAGE_RECIEVER_ABILITY_H
#define BF_DAMAGE_RECIEVER_ABILITY_H

#include "GameObjectComponents/AbilityComponent.h"
#include "GameStructs.h"
#include <bn_fixed_point.h>

class DamageRecieverAbility : public AbilityComponent{
public:
    
    DamageRecieverAbility() = default;
    virtual ~DamageRecieverAbility() = default;

protected:

public:
    virtual void Start() override;
    virtual bool UseAbility() override;

    virtual void GetDamage(const AttackInfo& atkInfo);
};

#endif