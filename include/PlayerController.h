#ifndef BF_PLAYER_CONTROLLER_H
#define BF_PLAYER_CONTROLLER_H

#include "PawnController.h"

#include "Player.h"

class PlayerController : public PawnController {
public:
    PlayerController();
    virtual ~PlayerController();

protected:
    Player* controlledPlayer;

public:
    virtual void Start() override;
    virtual void UpdateInput() override;

    virtual void Possess(Pawn* p) override;
    Pawn* GetControlledPlayer() { return controlledPawn; }
    virtual void Unpossess() override;

};

#endif