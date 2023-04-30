#include "Attack.h"
#include "Scenes/Scene.h"
#include "Character.h"
#include "GameManager.h"

#include "bn_sprite_items_slash_fx.h"
#include "bn_sprite_items_laser.h"

#define MELEE_SPRITE_SHEET bn::sprite_items::slash_fx
#define LASER_SPRITE bn::sprite_items::laser

void Attack::Start() {
    targets = GameManager::GetInstance()->GetCurrentGameScene()->GetAllInstancesCharacters();
    
    boxCollision.SetIsTrigger(true);
    SetupAnimations();
    if(!componentAdded) {
        AddComponent(&boxCollision);
        AddComponent(&animator);
        componentAdded = true;
    }
    
    GameObject::Start();
}

void Attack::Update() {
    GameObject::Update();

    if(attackInfo.projectileSpeed != 0) {
        UpdateMovement();
    }
    bool damage = false;
    for (int i = 0; i < targets.size(); ++i)  {
        if(targets[i] != nullptr && targets[i] != characterCreator && boxCollision.IsColliding(targets[i]->GetBoxCollision())) {
            DoDamage(targets[i]);
            damage = true;
        }
    }
    timeToLive--;
    if(timeToLive <= 0 || (damage && attackInfo.destroyOnCollision)) {
        GameManager::GetInstance()->GetCurrentGameScene()->DestroyAttack(this);
    }
}

void Attack::UpdateMovement() {
    AddLocalOffset(bn::fixed_point(attackInfo.projectileSpeed * currentDirection, 0));
    bn::fixed_point currentPos = GetWorldPosition();
    if(attackInfo.destroyOnCollision && mapCollision->GetCollisionByPosition(currentPos.x().floor_integer(), currentPos.y().floor_integer())) {
        GameManager::GetInstance()->GetCurrentGameScene()->DestroyAttack(this);
    }
}

void Attack::SetCharacterCreator(Character* cc) {
    characterCreator = cc;
}

void Attack::SetAttackInfo(const AttackInfo& aInfo) {
    attackInfo = aInfo;
    timeToLive = attackInfo.attackTimeToLive;
    SetupAnimations();
}

void Attack::SetupAnimations() {
    bn::vector<AnimInfo<16>, 1> anims;
    switch (attackInfo.attackType)
    {
        case AttackType::ATK_MELEE_SLASH:
            animator.SetSpriteItem(MELEE_SPRITE_SHEET);
            anims.emplace_back(AnimInfo<16>(bn::array<char, 16>{0,1,2,3,4}, 5, false));
            boxCollision.Setup(-16,-16,32,32);
            break;
        case AttackType::ATK_LASER_SHOT:
            animator.SetSpriteItem(LASER_SPRITE);
            anims.emplace_back(AnimInfo<16>(bn::array<char, 16>{0,0}, 1, false));
            boxCollision.Setup(-4,-2,8,4);
            break;
        
        default:
            break;
    }
    animator.SetAnimations(bn::move(anims));
    animator.ResetAnim();
}

void Attack::SetLayerDepth(int depth) {
    GameObject::SetLayerDepth(depth);
    animator.SetLayerDepth(layerDepth);
}

void Attack::SetZOrder(char z_order) {
    GameObject::SetZOrder(z_order);
    animator.SetZOrder(z_order);
}

void Attack::DoDamage(Character* other) {
    other->GetDamage(attackInfo, GetWorldPosition());
}

void Attack::SetDirection(int dir) {
    currentDirection = dir;
    animator.SetFlipped(dir == -1);
}