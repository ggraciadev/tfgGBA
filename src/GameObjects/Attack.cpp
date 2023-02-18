#include "Attack.h"
#include "Scene.h"
#include "Character.h"
#include "GameManager.h"
#include "bn_sprite_items_slash_fx.h"
#define SPRITE_SHEET bn::sprite_items::slash_fx

void Attack::Start() {
    targets = GameManager::GetInstance()->GetCurrentScene()->GetAllInstancesCharacters();
    boxCollision.Setup(-16,-16,32,32);
    boxCollision.SetIsTrigger(true);
    SetupAnimations();
    if(!componentAdded) {
        AddComponent(&boxCollision);
        AddComponent(&animator);
        componentAdded = true;
    }
    timeToLive = 25;
    
    GameObject::Start();
}

void Attack::Update() {
    GameObject::Update();
    
    for (int i = 0; i < targets.size(); ++i)  {
        if(targets[i] != nullptr && targets[i] != characterCreator && boxCollision.IsColliding(targets[i]->GetBoxCollision())) {
            DoDamage(targets[i]);
        }
    }
    timeToLive--;
    if(timeToLive <= 0) {
        //destroy
        GameManager::GetInstance()->GetCurrentScene()->DestroyAttack(this);
    }
    
}

void Attack::SetCharacterCreator(Character* cc) {
    characterCreator = cc;
}

void Attack::SetAttackInfo(const AttackInfo& aInfo) {
    attackInfo = aInfo;
}

void Attack::SetupAnimations() {
    animator.SetSpriteItem(SPRITE_SHEET);

    bn::vector<AnimInfo<16>, 1> anims;
    
    anims.emplace_back(AnimInfo<16>(bn::array<char, 16>{0,1,2,3,4}, 5, false));

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
    animator.SetFlipped(dir == -1);
}