#include "GameObjects/Player.h"
#include "GameObjectComponents/MeleeComboAbility.h"
#include "utils.h"
#include "GameObjects/Interactuable.h"
#include "GameManager.h"

#include "bn_sprite_items_character.h"
#define SPRITE_SHEET bn::sprite_items::character

void Player::Start() {
    input.SetPlayer(this);

    characterStats = CharacterStats(6, 6, 2, 1, 2,1);

    jumpAb.SetJumpSpeed(characterInfo.jumpSpeed);
    jumpAb.SetMaxJumps(MAX_JUMPS);
    jumpAb.SetMaxJumps(-1);
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
    // movement.SetGravityValue(0);
    // boxCollision.SetIsTrigger(true);
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
        AttackInfo(AttackType::ATK_MELEE_SLASH, 1, 1, 30, 25),
        AttackInfo(AttackType::ATK_MELEE_SLASH, 1, 1, 30, 25),
        AttackInfo(AttackType::ATK_MELEE_SLASH, 2, 2, 40, 25),
    });
}

void Player::Jump() {
    if(damageReciever.GetAbilityInUse()) return;
    if(jumpAb.UseAbility()) {
        animator.SetCurrentAnimation(2, true);
    }
}

void Player::Attack() {
    if(damageReciever.GetAbilityInUse()) return;
    if(currentInteractuable != nullptr) {
        currentInteractuable->Interact();
    }
    else if(meleeComboAb.UseAbility()) {
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

bool Player::GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) {
    bool result = false;
    int damage = Utils::Max((atkInfo.creatorStr + atkInfo.attackPower) / (characterStats.def * characterStats.defMulti), 1);
    bool salva = damage >= characterStats.currentHealth && characterStats.currentHealth > 1;
    result = damageReciever.GetDamage(atkInfo, attackPosition);
    if(result) {
        characterStats.currentHealth = Utils::Max(characterStats.currentHealth - damage, (int)salva);
        if(characterStats.currentHealth == 0) {
            Die();
        }
    }
    widgetHUD->SetCurrentHealth(characterStats.currentHealth);
    return result;
}

void Player::SetCurrentInteractuable(Interactuable* value, Interactuable* requested) { 
    if(value == nullptr && requested != currentInteractuable) { return; }
    if(currentInteractuable != nullptr) {
        currentInteractuable->SetGraphicEnabled(false);
    }
    currentInteractuable = value; 
    currentInteractuable->SetGraphicEnabled(true);
}

void Player::SetAtkPowerUp(bool powUp) {
    Character::SetAtkPowerUp(powUp);
    widgetHUD->SetStrPowerUp(powUp);
}

void Player::SetDefPowerUp(bool powUp) {
    Character::SetDefPowerUp(powUp);
    widgetHUD->SetDefPowerUp(powUp);
}

void Player::Die() {
    GameManager::GetInstance()->ChangeScene(GameScenes::SCENE_DEATH_MENU);
}