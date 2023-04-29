#include "GameObjects/Enemy.h"
#include "GameManager.h"


void Enemy::Start() {
    //input.SetPlayer(this);

    // jumpAb.SetJumpSpeed(characterInfo.jumpSpeed);
    // jumpAb.SetMaxJumps(MAX_JUMPS);
    // jumpAb.SetCharacter(this);

    // SetupAttacks();
    // meleeComboAb.SetCooldownCombo(COOLDOWN_COMBO);
    // meleeComboAb.SetCharacter(this);

    SetupAnimations();

    // AddComponent(&jumpAb);
    // AddComponent(&meleeComboAb);
    // AddComponent(&input);
    damageReciever.SetCharacter(this);
    //AddComponent(&animator);
    AddComponent(&damageReciever);
    SetPlayer(GameManager::GetInstance()->GetCurrentScene()->GetPlayer());

    Character::Start();
}

void Enemy::Update() {
    Character::Update();
    UpdateAnimationState();
}

void Enemy::GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) {
    Character::GetDamage(atkInfo, attackPosition);
    // if(damageReciever.GetAbilityInUse()) {
    //     animator.SetCurrentAnimation(1);
    // }
}

void Enemy::SetLayerDepth(int depth) {
    Character::SetLayerDepth(depth);
    // animator.SetLayerDepth(layerDepth);
}

void Enemy::SetZOrder(char z_order) {
    Character::SetZOrder(z_order);
    // animator.SetZOrder(z_order);
}

void Enemy::SetupAnimations() {
    // animator.SetSpriteItem(SPRITE_SHEET);

    // bn::vector<AnimInfo<2>, 2> anims;
    
    // anims.emplace_back(AnimInfo<2>(bn::array<char, 2>{0,0}, 1, true));
    // anims.emplace_back(AnimInfo<2>({1,1}, 1, true));

    // animator.SetAnimations(bn::move(anims));
}

void Enemy::SetupAttacks() {
    // meleeComboAb.SetAttackCombo({
    //     AttackInfo(10, 1, 20),
    //     AttackInfo(10, 1, 20),
    //     AttackInfo(20, 2, 30),
    // });
}

void Enemy::Jump() {
    // int lastJump = jumpAb.GetCurrentJump();
    // jumpAb.UseAbility();
    // if(lastJump != jumpAb.GetCurrentJump()) {
    //     animator.SetCurrentAnimation(2, true);
    // }
}

void Enemy::Attack() {
    // if(meleeComboAb.UseAbility()) {
    //     animator.SetCurrentAnimation(3);
    // }
}

void Enemy::Dash() {

}

void Enemy::UpdateAnimationState() {
    //if(meleeComboAb.GetAbilityInUse()) return;
    // animator.SetFlipped(movement.GetMovementDirection() == -1);
    // if(damageReciever.GetAbilityInUse()) return;
    // animator.SetCurrentAnimation(0);
}

void Enemy::Die() {
    
    GameManager::GetInstance()->GetCurrentScene()->SpawnEnemyCollectable(GetWorldPosition() + bn::fixed_point(0, 24));
    GameManager::GetInstance()->GetCurrentScene()->DestroyEnemy(this);
}