#include "ProjectileAttackAbility.h"
#include "Character.h"

void ProjectileAttackAbility::Start() {
    AttackAbility::Start();
    updateType = LOGIC_UPDATE;
}

bool ProjectileAttackAbility::UseAbility() {
    abilityDuration = attackInfo.attackDuration;
    bool ret = AttackAbility::UseAbility();
    if(ret) {
        SpawnAttack(attackInfo, false);
    }
    return ret;
}

void ProjectileAttackAbility::Update() {
    AttackAbility::Update();
}
