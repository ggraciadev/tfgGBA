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

public:
    virtual void UseAbility() {};

    inline void SetCharacter(Character* c) { character= c;}

};

#endif