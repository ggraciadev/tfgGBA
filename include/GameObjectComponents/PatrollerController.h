#ifndef BF_PATROLLER_CONTROLLER_H
#define BF_PATROLLER_CONTROLLER_H

#include "GameObjectComponents/AIController.h"

#include <bn_fixed_point.h>

class MapCollision;

class PatrollerController : public AIController{
public:
    
    PatrollerController() = default;
    virtual ~PatrollerController() = default;

protected:
    int attackCooldown;
    int currentAttackCooldown;

    int stopTimeTurn;
    int currentStopTimeTurn;

    int currentDirection;

    bool stopped;

    int checkGroundHeight = 32;

    bn::fixed_point attackDist;
    MapCollision* mapCollision;

public:
    virtual void Start() override;
    virtual void Update() override;

    void UpdateTimers();

    bool CheckToAttack();
    void Attack();
    bool CheckToMove();
    void Move();
    void ChangeDirection();
    inline void SetCheckGroundHeight(int height) { checkGroundHeight = height; }

    inline void SetAttackDist(bn::fixed_point dist) { attackDist = dist; }

    inline void SetMapCollisions(MapCollision* mCol) { mapCollision = mCol; }

};

#endif