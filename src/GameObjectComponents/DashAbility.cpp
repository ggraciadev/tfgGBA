#include "DashAbility.h"
#include "Character.h"

void DashAbility::Start() {
    currentDuration = 0;
    abilityDuration = 20;
    updateType = LOGIC_UPDATE;
    AbilityComponent::Start();
}

bool DashAbility::UseAbility() {
    bool ret = AbilityComponent::UseAbility();
    if(ret) {
        character->GetMovementComponent()->AddImpulseForward(dashSpeed, abilityDuration);
        return true;
    }
    return false;
}