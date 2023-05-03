#include "PatrollerController.h"
#include "GameObjects/Enemy.h"
#include "GameObjectComponents/MapCollision.h"
#include "utils.h"

void PatrollerController::Start() {
    AIController::Start();
    attackCooldown = 120;
    currentAttackCooldown = attackCooldown;

    stopTimeTurn = 60;
    currentStopTimeTurn = stopTimeTurn;

    stopped = true;

    currentDirection = 1;
}

void PatrollerController::Update() {
    AIController::Update();
    UpdateTimers();
    if(CheckToAttack()) {
        Attack();
    }
    else if(CheckToMove()) {
        Move();
    }
}

void PatrollerController::UpdateTimers() {
    if(stopped) {
        currentStopTimeTurn --;
        if(currentStopTimeTurn <= 0) {
            stopped = false;
        }
    }
    if(currentAttackCooldown > 0) {
        currentAttackCooldown--;
    }
}

bool PatrollerController::CheckToAttack() {
    bool result = currentAttackCooldown <= 0;
    if(result) {
        bn::fixed_point dist = player->GetWorldPosition() - enemy->GetWorldPosition();
        result = Utils::Abs(dist.x()) < attackDist.x() &&  Utils::Abs(dist.y() < attackDist.y());
    }

    return result;
}
void PatrollerController::Attack() {
    bn::fixed_point dist = player->GetWorldPosition() - enemy->GetWorldPosition();
    if(dist.x() < 0) {
        currentDirection = -1;
    }
    else {
        currentDirection = 1;
    }
    enemy->GetMovementComponent()->SetMovementDirection(currentDirection);
    currentAttackCooldown = attackCooldown;
    stopped = true;
    currentStopTimeTurn = 20;
    enemy->SetInputMovementX(0);
    enemy->Attack();
}
bool PatrollerController::CheckToMove() {
    if(stopped) return false;
    bool result = true;
    bn::fixed_point pos = enemy->GetWorldPosition();
    pos.set_x(pos.x() + currentDirection * 16); 
    
    //miramos el tile de el lado hacia donde se mueve si no es colision
    if(mapCollision->GetCollisionByPosition(pos.x().floor_integer(), pos.y().floor_integer()) != MapCollisionType::ROOM_INTERIOR) {
        result = false;
    }
    if(result) {
        //miramos el tile de abajo del anterior para ver si hay suelo
        pos.set_y(pos.y() + checkGroundHeight);

        if(mapCollision->GetCollisionByPosition(pos.x().floor_integer(), pos.y().floor_integer()) == MapCollisionType::ROOM_INTERIOR) {
            result = false;
        }
    }

    if(!result) {
        ChangeDirection();
    }

    return result;
}
void PatrollerController::Move() {
    enemy->SetInputMovementX(currentDirection);
}

void PatrollerController::ChangeDirection() {
    stopped = true;
    currentStopTimeTurn = stopTimeTurn;
    currentDirection *= -1;
    enemy->SetInputMovementX(0);
}