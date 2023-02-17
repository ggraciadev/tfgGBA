#include "GameObjectComponents/AttackAbility.h"
#include "GameManager.h"
#include "Scene.h"
#include "GameObjects/Attack.h"

void AttackAbility::SpawnAttack(AttackInfo& attackInfo) {
    GameManager::GetInstance()->GetCurrentScene()->SpawnAttack((GameObject*)character, bn::fixed_point(0, 0), attackInfo);
}