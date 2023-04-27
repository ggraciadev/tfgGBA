#include "GameObjectComponents/AttackAbility.h"
#include "GameManager.h"
#include "Scene.h"
#include "GameObjects/Attack.h"

void AttackAbility::SpawnAttack(AttackInfo& attackInfo, bool attachToCreator) {
    bn::fixed_point spawnPos = spawnOffset;
    int direction = character->GetMovementComponent()->GetMovementDirection();
    spawnPos.set_x(spawnOffset.x() * direction);
    GameObject* parent = nullptr;
    if(attachToCreator) parent = character;
    GameManager::GetInstance()->GetCurrentScene()->SpawnAttack(parent, character, spawnPos, direction, attackInfo);
}