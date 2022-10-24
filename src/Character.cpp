#include "Character.h"
#include "MapCollision.h"

Character::Character() {
    
}

Character::~Character() {

}

void Character::Start() {   
    movement.SetCurrentMovementSpeed(2);
    input.SetCharacter(this);
    boxCollision.Setup(COLLISION_OFFSET_X, COLLISION_OFFSET_Y, COLLISION_WIDTH, COLLISION_HEIGHT);

    AddComponent(&movement);
    AddComponent(&input);
    AddComponent(&boxCollision);
    AddComponent(&animator);

    GameObject::Start();
}

void Character::SetMapCollision(MapCollision* mc) {
    boxCollision.SetMapCollision(mc);
}

void Character::Update() {
    GameObject::Update();
}

void Character::PhysicsUpdate() {
    GameObject::PhysicsUpdate();
    boxCollision.PhysicsUpdate();
    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
    }
}

void Character::Render() {
    GameObject::Render();
    animator.Render();
}

void Character::SetLayerDepth(int depth) {
    SetZOrder(1);
    GameObject::SetLayerDepth(depth);
    animator.SetLayerDepth(layerDepth);
}

void Character::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    animator.SetZOrder(z_order);
}

void Character::Jump() {
    movement.SetVelocityY(JUMP_SPEED);
}

void Character::SetInputMovement(bn::fixed_point md) {
    movement.SetInputMovement(md);
    if(boxCollision.GetContact(RIGHT_COLLISION) && movement.GetVelocity().x() > 0) {
        movement.SetVelocityX(0);
    }
    else if(boxCollision.GetContact(LEFT_COLLISION) && movement.GetVelocity().x() < 0) {
        movement.SetVelocityX(0);
    }
    if(md.x() > 0.0f) {
        animator.SetFlipped(false);
    }
    else if (md.x() < 0.0f) {
        animator.SetFlipped(true);
    }
    
    if(md.x() == 0.0f) {
        animator.SetCurrentAnimation(0);
    }
    else {
        animator.SetCurrentAnimation(1);
    }
}

void Character::SetInputMovementX(bn::fixed x) {
    movement.SetInputMovementX(x);
    if(boxCollision.GetContact(RIGHT_COLLISION) && movement.GetVelocity().x() > 0) {
        movement.SetVelocityX(0);
    }
    else if(boxCollision.GetContact(LEFT_COLLISION) && movement.GetVelocity().x() < 0) {
        movement.SetVelocityX(0);
    }
    if(x > 0.0f) {
        animator.SetFlipped(false);
    }
    else if (x < 0.0f) {
        animator.SetFlipped(true);
    }
    if(x == 0.0f) {
        animator.SetCurrentAnimation(0);
    }
    else {
        animator.SetCurrentAnimation(1);
    }
}

void Character::SetInputMovementY(bn::fixed y) {
    movement.SetInputMovementY(y);
}