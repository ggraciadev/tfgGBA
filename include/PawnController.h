#ifndef BF_ACTOR_CONTROLLER_H
#define BF_ACTOR_CONTROLLER_H

#include "bn_core.h"
#include <bn_fixed_point.h>

class Pawn;

class PawnController {
public:
    PawnController();
    virtual ~PawnController();

protected:
    Pawn* controlledPawn;
    bn::fixed_point inputMovement;

public:
    virtual void Start();
    virtual void Update();
    virtual void UpdateInput();

    virtual void Possess(Pawn* p);
    Pawn* GetControlledPawn() { return controlledPawn; }
    virtual void Unpossess();

};

#endif