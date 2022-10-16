#ifndef BF_PLAYER_H
#define BF_PLAYER_H

#include "Entity.h"

class Player : public Entity {
public:
    Player();
    Player(const int posX, const int posY, GameObject* _parent = nullptr, const bn::fixed gravity = 0);

    virtual ~Player();

protected:

public:

};

#endif