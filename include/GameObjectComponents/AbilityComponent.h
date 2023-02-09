#ifndef BF_ABILITY_COMPONENT_H
#define BF_ABILITY_COMPONENT_H

#include "GameObjectComponents/GameObjectComponent.h"

#include <bn_fixed_point.h>

class Character;

class AbilityComponent : public GameObjectComponent{
public:
    
    AbilityComponent() = default;
    virtual ~AbilityComponent() = default;

protected:
    Character* character;
    int abilityDuration;
    int currentDuration;
    bool abilityInUse;

public:
    virtual bool UseAbility();
    virtual void Update() override;

    inline void SetCharacter(Character* c) { character= c;}
    inline void SetAbilityDuration(const int duration) { abilityDuration = duration; }
    inline bool GetAbilityInUse() const { return abilityInUse; }

};

#endif