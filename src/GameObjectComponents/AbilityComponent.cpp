#include "AbilityComponent.h"

void AbilityComponent::Update() {
    if(abilityInUse) {
        currentDuration--;
    }
}

bool AbilityComponent::UseAbility() {
    if(abilityInUse) { return false; }
    abilityInUse = true;
    currentDuration = abilityDuration;
    return true;
}