#ifndef BF_COLLECTABLE_ITEM_H
#define BF_COLLECTABLE_ITEM_H

#include "GameObjects/Interactuable.h"

class CollectableItem : public Interactuable {
public:

    CollectableItem() = default;
    ~CollectableItem() = default;

protected:

public:
    void Start();

    virtual void Interact();
    
    virtual void InitSprite(const bn::sprite_item& item);

};

#endif