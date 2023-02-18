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
    float damageCooldown;
    float currentDamageCooldown;

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual bool UseAbility() override;

    virtual bool GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition);
    inline void SetDamageCooldown(const float cooldown) { damageCooldown = cooldown; }
};

#endif