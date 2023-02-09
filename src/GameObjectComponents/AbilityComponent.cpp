#include "AbilityComponent.h"

void AbilityComponent::Update() {
    if(abilityInUse) {
        currentDuration--;
        if(currentDuration <= 0) abilityInUse = false;
    }
}

bool AbilityComponent::UseAbility() {
    if(abilityInUse) { return false; }
    abilityInUse = true;
    currentDuration = abilityDuration;
    return true;
}