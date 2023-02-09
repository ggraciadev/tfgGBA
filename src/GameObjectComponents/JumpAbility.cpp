#include "JumpAbility.h"
#include "Character.h"

void JumpAbility::Start() {
    AbilityComponent::Start();
    abilityDuration = 0;
    currentDuration = 0;
    updateType = NO_UPDATE;
}

bool JumpAbility::UseAbility() {
    if(character->GetMovementComponent()->IsGrounded()) {
        currentJumps = 0;
    }
    if(currentJumps < maxJumps) {
        character->GetMovementComponent()->SetVelocityY(jumpSpeed);
        currentJumps++;
    }
}