#ifndef BF_ATTACK_ABILITY_H
#define BF_ATTACK_ABILITY_H

#include "GameObjectComponents/AbilityComponent.h"
#include "GameStructs.h"
#include <bn_fixed_point.h>

class AttackAbility : public AbilityComponent{
public:
    
    AttackAbility() = default;
    virtual ~AttackAbility() = default;

protected:

public:

    void SpawnAttack(AttackInfo& attackInfo);

};

#endif