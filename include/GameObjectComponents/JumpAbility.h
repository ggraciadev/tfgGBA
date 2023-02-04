#ifndef BF_JUMP_ABILITY_H
#define BF_JUMP_ABILITY_H

#include "GameObjectComponents/AbilityComponent.h"

#include <bn_fixed_point.h>

class JumpAbility : public AbilityComponent{
public:
    
    JumpAbility() = default;
    virtual ~JumpAbility() = default;

protected:
    int jumpSpeed = 4;
    int maxJumps = 1;

    int currentJumps = 0;

public:
    virtual void UseAbility() override;

    inline void SetJumpSpeed(int s) { jumpSpeed = s; }
    inline int GetJumpSpeed() const { return jumpSpeed; }
    inline void SetMaxJumps(int jumps) { maxJumps = jumps; }

};

#endif