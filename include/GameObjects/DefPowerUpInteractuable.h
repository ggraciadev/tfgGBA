#ifndef BF_DEF_POWERUP_INTERACTUABLE_H
#define BF_DEF_POWERUP_INTERACTUABLE_H

#include "GameObjects/Interactuable.h"

class DefPowerUpInteractuable : public Interactuable {
public:

    DefPowerUpInteractuable() = default;
    ~DefPowerUpInteractuable() = default;

protected:

public:
    virtual void Start();

    virtual void Interact();
    
    virtual void InitSprite(const bn::sprite_item& item);

};

#endif