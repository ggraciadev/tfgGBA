#include "JumpAbility.h"
#include "Character.h"

void JumpAbility::Start() {
    abilityDuration = 0;
    currentDuration = 0;
    currentJumps = 0;
    updateType = NO_UPDATE;
    AbilityComponent::Start();
}

bool JumpAbility::UseAbility() {
    if(character->GetMovementComponent()->IsGrounded()) {
        currentJumps = 0;
    }
    if(maxJumps == -1 || currentJumps < maxJumps) {
        character->GetMovementComponent()->SetVelocityY(jumpSpeed);
        currentJumps++;
        return true;
    }
    return false;
}