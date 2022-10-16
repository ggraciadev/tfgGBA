#ifndef BF_PAWN_H
#define BF_PAWN_H

#include "Actor.h"

class PawnController;

class Pawn : public Actor{
public:
    Pawn();
    Pawn(const int posX, const int posY, GameObject* _parent = nullptr, const bn::fixed gravity = 0);

    virtual ~Pawn();

protected:
    virtual void Start() override;
    virtual void Update() override;

    PawnController* controller;

public:

    PawnController* GetController() { return controller; }
    void SetPawnController(PawnController* pc);
    PawnController* GetPawnController() { return controller; }
};

#endif