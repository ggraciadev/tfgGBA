#include "GameObjects/Character.h" 
#include "GameObjectComponents/MapCollision.h"
#include "bn_sprite_items_character.h"
#define SPRITE_SHEET bn::sprite_items::character

void Character::Start() {   
    movement.SetCurrentMovementSpeed(1.5); 
    input.SetCharacter(this);
    boxCollision.Setup(COLLISION_OFFSET_X, COLLISION_OFFSET_Y, COLLISION_WIDTH, COLLISION_HEIGHT);
    

    

    SetupAnimations();

    jumpAb.SetJumpSpeed(JUMP_SPEED);
    jumpAb.SetMaxJumps(2);
    jumpAb.SetCharacter(this);

    AddComponent(&boxCollision);
    AddComponent(&input);
    AddComponent(&movement);
    AddComponent(&animator);
    AddComponent(&jumpAb);

    GameObject::Start();
}

void Character::SetupAnimations() {
    animator.SetSpriteItem(SPRITE_SHEET);

    animator.SetAnimations({
        AnimInfo<16>({0,0,1,1,2,2,3,3,4,4,5,5,6,6}, 14, true, false),
        AnimInfo<16>({7,8,9,10,11,12,13,14,15,16,12}, 11, true, false),
        AnimInfo<16>({19,20,20,21,21,22,22,23,23}, 9, false, true),
        AnimInfo<16>({24,25,26,27,28}, 5, false, true)
    });
}

void Character::SetMapCollision(MapCollision* mc) {
    boxCollision.SetMapCollision(mc);
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
    int lastJump = jumpAb.GetCurrentJump();
    jumpAb.UseAbility();
    if(lastJump != jumpAb.GetCurrentJump()) {
        animator.SetCurrentAnimation(2, true);
    }
}

void Character::SetInputMovement(bn::fixed_point md) {
    if(md.x() > 0.0f) {
        if(boxCollision.GetContact(RIGHT_COLLISION)) {
            md.set_x(0);
            movement.SetVelocityX(0);
        }
        animator.SetFlipped(false);
    }
    else if (md.x() < 0.0f) {
        if(boxCollision.GetContact(LEFT_COLLISION)) {
            md.set_x(0);
            movement.SetVelocityX(0);
        }
        animator.SetFlipped(true);
    }
    movement.SetInputMovement(md);

    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
    }
    if(movement.IsGrounded()) {
        if(md.x() == 0.0f) {
            animator.SetCurrentAnimation(0);
        }
        else {
            animator.SetCurrentAnimation(1);
        }
    }
    else {
        animator.SetCurrentAnimation(2);
    }

}

void UpdateAnimationState() {
    
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
    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
    }
}

void Character::SetInputMovementY(bn::fixed y) {
    movement.SetInputMovementY(y);
}