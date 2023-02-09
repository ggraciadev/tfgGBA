#include "GameObjects/Player.h"

#include "bn_sprite_items_character.h"
#define SPRITE_SHEET bn::sprite_items::character

void Player::Start() {
    input.SetPlayer(this);

    jumpAb.SetJumpSpeed(characterInfo.jumpSpeed);
    jumpAb.SetMaxJumps(MAX_JUMPS);
    jumpAb.SetCharacter(this);

    SetupAttacks();
    meleeComboAb.SetCooldownCombo(COOLDOWN_COMBO);
    meleeComboAb.SetCharacter(this);

    SetupAnimations();

    AddComponent(&jumpAb);
    AddComponent(&meleeComboAb);
    AddComponent(&input);
    AddComponent(&animator);

    Character::Start();
}

void Player::Update() {
    Character::Update();
    UpdateAnimationState();
}

void Player::SetLayerDepth(int depth) {
    Character::SetLayerDepth(depth);
    animator.SetLayerDepth(layerDepth);
}

void Player::SetZOrder(char z_order) {
    Character::SetZOrder(z_order);
    animator.SetZOrder(z_order);
}

void Player::SetupAnimations() {
    animator.SetSpriteItem(SPRITE_SHEET);

    animator.SetAnimations({
        AnimInfo<16>({0,0,1,1,2,2,3,3,4,4,5,5,6,6}, 14, true, false),
        AnimInfo<16>({7,8,9,10,11,12,13,14,15,16,12}, 11, true, false),
        AnimInfo<16>({19,20,20,21,21,22,22,23,23}, 9, false, true),
        AnimInfo<16>({24,25,26,27,28}, 5, false, true)
    });
}

void Player::SetupAttacks() {
    meleeComboAb.SetAttackCombo({
        AttackInfo(10, 1, 20),
        AttackInfo(10, 1, 20),
        AttackInfo(20, 2, 30),
    });
}

void Player::Jump() {
    int lastJump = jumpAb.GetCurrentJump();
    jumpAb.UseAbility();
    if(lastJump != jumpAb.GetCurrentJump()) {
        animator.SetCurrentAnimation(2, true);
    }
}

void Player::Attack() {
    if(meleeComboAb.UseAbility()) {
        animator.SetCurrentAnimation(3);
    }
}

void Player::Dash() {

}

void Player::UpdateAnimationState() {
    if(meleeComboAb.GetAbilityInUse()) return;
    if(movement.IsGrounded()) {
        if(movement.GetInputMovement().x() == 0.0f) {
            animator.SetCurrentAnimation(0);
        }
        else {
            animator.SetCurrentAnimation(1);
        }
    }
    else {
        animator.SetCurrentAnimation(2);
    }

    animator.SetFlipped(movement.GetMomvementDirection() == -1);
}