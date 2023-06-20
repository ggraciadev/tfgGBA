#ifndef BF_DASH_ABILITY_OBTAINER_H
#define BF_DASH_ABILITY_OBTAINER_H

#include "GameObjects/Interactuable.h"

class DashAbilityObtainer : public Interactuable {
public:

    DashAbilityObtainer() = default;
    ~DashAbilityObtainer() = default;

protected:

public:
    virtual void Start();

    virtual void Interact();
    
    virtual void InitSprite(const bn::sprite_item& item);

};

#endif