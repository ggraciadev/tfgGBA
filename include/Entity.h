#ifndef BF_ENTITY_H
#define BF_ENTITY_H

#include "Pawn.h"

class Entity : public Pawn{
public:
    Entity();
    Entity(const int posX, const int posY, GameObject* _parent = nullptr, const bn::fixed gravity = 0);

    virtual ~Entity();

protected:

public:

};

#endif