#include "GameObjects/Character.h" 
#include "GameObjectComponents/MapCollision.h"
#include "bn_sprite_items_character.h"
#define SPRITE_SHEET bn::sprite_items::character

void Character::Start() {   
    movement.SetCurrentMovementSpeed(1.5); 
    input.SetCharacter(this);
    boxCollision.Setup(COLLISION_OFFSET_X, COLLISION_OFFSET_Y, COLLISION_WIDTH, COLLISION_HEIGHT);
    animator.SetSpriteItem(SPRITE_SHEET);

    AddComponent(&boxCollision);
    AddComponent(&input);
    AddComponent(&movement);
    AddComponent(&animator);

    GameObject::Start();
}

void Character::SetMapCollision(MapCollision* mc) {
    boxCollision.SetMapCollision(mc);
}

void Character::SetLayerDepth(int depth) {
    SetZOrder(1);
    GameObject::SetLayerDepth(depth);
    animator.SetLayerDepth(data.layerDepth);
}

void Character::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    animator.SetZOrder(z_order);
}

void Character::Jump() {
    movement.SetVelocityY(JUMP_SPEED);
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
    
    if(md.x() == 0.0f) {
        animator.SetCurrentAnimation(0);
    }
    else {
        animator.SetCurrentAnimation(1);
    }
    movement.SetInputMovement(md);

    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
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
    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
    }
}

void Character::SetInputMovementY(bn::fixed y) {
    movement.SetInputMovementY(y);
}