#include "JumpAbility.h"
#include "Character.h"

void JumpAbility::UseAbility() {
    if(character->GetMovementComponent()->IsGrounded()) {
        currentJumps = 0;
    }
    if(currentJumps < maxJumps) {
        character->GetMovementComponent()->SetVelocityY(jumpSpeed);
        currentJumps++;
    }
}