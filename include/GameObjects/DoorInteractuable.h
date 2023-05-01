#ifndef BF_DOOR_INTERACTUABLE_H
#define BF_DOOR_INTERACTUABLE_H

#include "GameObjects/Interactuable.h"

class DoorInteractuable : public Interactuable {
public:

    DoorInteractuable() = default;
    ~DoorInteractuable() = default;

protected:
    int nextGameSceneSeed;

public:
    virtual void Start();

    virtual void Interact();
    
    virtual void InitSprite(const bn::sprite_item& item);

    inline void NextGameSceneSeed(int seed) { nextGameSceneSeed = seed; }

};

#endif