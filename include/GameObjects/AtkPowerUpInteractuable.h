#ifndef BF_ATK_POWERUP_INTERACTUABLE_H
#define BF_ATK_POWERUP_INTERACTUABLE_H

#include "GameObjects/Interactuable.h"

class AtkPowerUpInteractuable : public Interactuable {
public:

    AtkPowerUpInteractuable() = default;
    ~AtkPowerUpInteractuable() = default;

protected:

public:
    void Start();

    virtual void Interact();
    
    virtual void InitSprite(const bn::sprite_item& item);

};

#endif