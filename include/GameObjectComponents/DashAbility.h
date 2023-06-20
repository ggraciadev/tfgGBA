#ifndef BF_DASH_ABILITY_H
#define BF_DASH_ABILITY_H

#include "GameObjectComponents/AbilityComponent.h"

#include <bn_fixed_point.h>

class DashAbility : public AbilityComponent{
public:
    
    DashAbility() = default;
    virtual ~DashAbility() = default;

protected:
    int dashSpeed = 6;

public:
    virtual void Start() override;
    virtual bool UseAbility() override;

    inline void SetDashSpeed(int s) { dashSpeed = s; }
    inline int GetDashSpeed() { return dashSpeed; }

};

#endif