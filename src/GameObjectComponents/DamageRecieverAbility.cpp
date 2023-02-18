#include "DamageRecieverAbility.h"
#include "Character.h"

void DamageRecieverAbility::Start() {
    updateType = LOGIC_UPDATE;
    currentDamageCooldown = 0;
    AbilityComponent::Start();
}

bool DamageRecieverAbility::UseAbility() {
    bool result = AbilityComponent::UseAbility();
    return result;
}

void DamageRecieverAbility::Update() {
    AbilityComponent::Update();
    if(currentDamageCooldown > 0) {
        currentDamageCooldown--;
    }
}

bool DamageRecieverAbility::GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) {
    //setteo de duracion y tal
    bool result = false;
    if(currentDamageCooldown <= 0) {
        abilityDuration = atkInfo.attackDuration;
        result = UseAbility();
        if(result) {
            bn::fixed_point dirVect = attackPosition - character->GetWorldPosition();
            int dir = 1;
            if(dirVect.x() < 0) {
                dir = -1;
            }
            currentDamageCooldown = damageCooldown;
            character->GetMovementComponent()->SetMovementDirection(dir);
            character->GetMovementComponent()->AddImpulseBackward(atkInfo.impulseSpeed, abilityDuration);
        }
    }

    return result;
}