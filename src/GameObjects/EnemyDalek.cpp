#include "GameObjects/EnemyDalek.h"
#include "GameManager.h"

#include "bn_sprite_items_mini_dalek.h"
#define SPRITE_SHEET bn::sprite_items::mini_dalek


void EnemyDalek::Start() {
    //input.SetPlayer(this);
    patrollerController.SetEnemy(this);
    patrollerController.SetAttackDist(bn::fixed_point(200, 50));
    patrollerController.SetCheckGroundHeight(16);
    characterStats = CharacterStats(2, 2, 2, 1, 2, 1);
    characterInfo.boxCollisionExtension = BoxExtension(bn::fixed_point(-16, -20), bn::fixed_point( 32, 32));

    // jumpAb.SetJumpSpeed(characterInfo.jumpSpeed);
    // jumpAb.SetMaxJumps(MAX_JUMPS);
    // jumpAb.SetCharacter(this);

    SetupAttacks();
    
    damageReciever.SetCharacter(this);

    SetupAnimations();
    AddComponent(&laserAttackAb);
    AddComponent(&patrollerController);
    AddComponent(&animator);
    AddComponent(&damageReciever);

    Enemy::Start();
}

void EnemyDalek::SetPlayer(Character* p) {
    Enemy::SetPlayer(p);
    patrollerController.SetPlayer(p);
}

void EnemyDalek::SetMapCollision(MapCollision* mc) {
    Enemy::SetMapCollision(mc);
    patrollerController.SetMapCollisions(mc);
}

void EnemyDalek::Update() {
    Enemy::Update();
    UpdateAnimationState();
}

bool EnemyDalek::GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) {
    bool result = Enemy::GetDamage(atkInfo, attackPosition);
    if(damageReciever.GetAbilityInUse()) {
        animator.SetCurrentAnimation(2);
    }
    return result;
}

void EnemyDalek::SetLayerDepth(int depth) {
    Enemy::SetLayerDepth(depth);
    animator.SetLayerDepth(layerDepth);
}

void EnemyDalek::SetZOrder(char z_order) {
    Enemy::SetZOrder(z_order);
    animator.SetZOrder(z_order);
}

void EnemyDalek::SetupAnimations() {
    animator.SetSpriteItem(SPRITE_SHEET);

    bn::vector<AnimInfo<8>, 3> anims;
    
    anims.emplace_back(AnimInfo<8>({0,0}, 1, true));
    anims.emplace_back(AnimInfo<8>({1,1,2,2,3,3,4,4}, 8, false));
    anims.emplace_back(AnimInfo<8>({6,6,7,7,6,6, 0,0}, 8, false));

    animator.SetAnimations(bn::move(anims));
}

void EnemyDalek::SetupAttacks() {
    laserAttackAb.SetAttackInfo(AttackInfo(AttackType::ATK_LASER_SHOT, 1, 1, 10, 60, 5, true));
    laserAttackAb.SetCharacter(this);
    laserAttackAb.SetSpawnOffset(bn::fixed_point(32, 0));
}

void EnemyDalek::Jump() {
    // int lastJump = jumpAb.GetCurrentJump();
    // jumpAb.UseAbility();
    // if(lastJump != jumpAb.GetCurrentJump()) {
    //     animator.SetCurrentAnimation(2, true);
    // }
}

void EnemyDalek::Attack() {
    // if(meleeComboAb.UseAbility()) {
    //     animator.SetCurrentAnimation(3);
    // }
    if(damageReciever.GetAbilityInUse()) return;
    Enemy::Attack();
    if(laserAttackAb.UseAbility()) {
        animator.SetCurrentAnimation(1);
    }
}

void EnemyDalek::Dash() {

}

void EnemyDalek::UpdateAnimationState() {
    //if(meleeComboAb.GetAbilityInUse()) return;
    animator.SetFlipped(movement.GetMovementDirection() == -1);
    if(damageReciever.GetAbilityInUse()) return;
    if(!laserAttackAb.GetAbilityInUse()) {
        animator.SetCurrentAnimation(0);
    }
}

void EnemyDalek::Die() {
    rand.set_seed(seed);
    int random = rand.get_int(0,100);
    if(random < 30) {
        
    }
    else if(random < 50) {
        GameManager::GetInstance()->GetCurrentGameScene()->SpawnHealthRecovery(GetWorldPosition());
    }
    else if(random < 70) {
        GameManager::GetInstance()->GetCurrentGameScene()->SpawnEnemyCollectable(GetWorldPosition());
    }
    else if(random < 85) {
        GameManager::GetInstance()->GetCurrentGameScene()->SpawnAtkPowerUp(GetWorldPosition());
    }
    else if(random < 100) {
        GameManager::GetInstance()->GetCurrentGameScene()->SpawnDefPowerUp(GetWorldPosition());
    }
    Enemy::Die();
}