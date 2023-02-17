#include "DamageRecieverAbility.h"
#include "Character.h"

void DamageRecieverAbility::Start() {
    AbilityComponent::Start();
    updateType = LOGIC_UPDATE;
}

bool DamageRecieverAbility::UseAbility() {
    bool result = AbilityComponent::UseAbility();
    if(result) {
        //impulse back
    }
    return result;
}

void DamageRecieverAbility::GetDamage(const AttackInfo& atkInfo) {
    //setteo de duracion y tal
    UseAbility();
}