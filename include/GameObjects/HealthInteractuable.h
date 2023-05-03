#ifndef BF_HEALTH_INTERACTUABLE_H
#define BF_HEALTH_INTERACTUABLE_H

#include "GameObjects/Interactuable.h"

class HealthInteractuable : public Interactuable {
public:

    HealthInteractuable() = default;
    ~HealthInteractuable() = default;

protected:

public:
    virtual void Start();

    virtual void Interact();
    
    virtual void InitSprite(const bn::sprite_item& item);

};

#endif