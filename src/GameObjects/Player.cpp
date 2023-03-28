#include "GameObjects/Player.h"
#include "GameObjectComponents/MeleeComboAbility.h"

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
    meleeComboAb.SetSpawnOffset(bn::fixed_point(10, 0));

    SetupAnimations();

    AddComponent(&jumpAb);
    AddComponent(&meleeComboAb);
    AddComponent(&input);
    AddComponent(&animator);

    

    Character::Start();
    movement.SetGravityValue(0);
    boxCollision.SetIsTrigger(true);
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

    bn::vector<AnimInfo<16>, 4> anims;
    
    anims.emplace_back(AnimInfo<16>(bn::array<char, 16>{0,0,1,1,2,2,3,3,4,4,5,5,6,6}, 14, true));
    anims.emplace_back(AnimInfo<16>({7,8,9,10,11,12,13,14,15,16,12}, 11, true));
    anims.emplace_back(AnimInfo<16>({19,20,20,21,21,22,22,23,23}, 9, false));
    anims.emplace_back(AnimInfo<16>({24,25,26,27,28}, 5, false));

    animator.SetAnimations(bn::move(anims));
}

void Player::SetupAttacks() {
    meleeComboAb.SetAttackCombo({
        AttackInfo(10, 1, 20),
        AttackInfo(10, 1, 20),
        AttackInfo(20, 2, 30),
    });
}

void Player::Jump() {
    if(jumpAb.UseAbility()) {
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

    animator.SetFlipped(movement.GetMovementDirection() == -1);
}