#include "GameObjectComponents/AttackAbility.h"
#include "GameManager.h"
#include "Scene.h"
#include "GameObjects/Attack.h"

void AttackAbility::SpawnAttack(AttackInfo& attackInfo) {
    bn::fixed_point spawnPos = spawnOffset;
    int direction = character->GetMovementComponent()->GetMovementDirection();
    spawnPos.set_x(spawnOffset.x() * direction);
    GameManager::GetInstance()->GetCurrentScene()->SpawnAttack(character, character, spawnPos, direction, attackInfo);
}