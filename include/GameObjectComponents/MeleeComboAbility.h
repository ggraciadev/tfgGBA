#ifndef BF_MELEE_COMBO_ABILITY_H
#define BF_MELEE_COMBO_ABILITY_H

#include "GameObjectComponents/AttackAbility.h"
#include <bn_fixed_point.h>

class Character;

template <int MAX_COMBO>
class MeleeComboAbility : public AttackAbility{
public:
    
    MeleeComboAbility() = default;
    virtual ~MeleeComboAbility() = default;

protected:

    AttackInfo attacksCombo [MAX_COMBO];
    int currentCombo = 0;
    int cooldownCombo = 0;
    int currentCooldown = 0;
    int currentFrame = 0;
    int resetCombo = 0;

public:
    virtual bool UseAbility() override;
    virtual void Update() override;
    virtual void Start() override;
    

    inline void SetCooldownCombo(int cooldown) { cooldownCombo = cooldown; }
    inline int GetCurrentCombo() const { return currentCombo; }
    void SetAttackCombo(const AttackInfo (&info)[MAX_COMBO]) { 
        for(int i = 0; i < MAX_COMBO; ++i) attacksCombo[i] = info[i];
    }
    inline AttackInfo& GetAttackInfo(const int index) const { return attacksCombo[index]; }

};

#include "Character.h"

template <int MAX_COMBO>
void MeleeComboAbility<MAX_COMBO>::Start() {
    AbilityComponent::Start();
    updateType = LOGIC_UPDATE;
}

template <int MAX_COMBO>
bool MeleeComboAbility<MAX_COMBO>::UseAbility() {
    
    if(currentCooldown > 0 || currentCombo >= MAX_COMBO) { return false; }
    abilityDuration = attacksCombo[currentCombo].attackDuration;
    bool ret = AbilityComponent::UseAbility();
    if(ret) {
        SpawnAttack(attacksCombo[currentCombo]);
        character->GetMovementComponent()->AddImpulseForward(attacksCombo[currentCombo].impulseSpeed, 20);
        currentCombo++;
        if(currentCombo >= MAX_COMBO) {
            currentCooldown = cooldownCombo;
        }
    }
    return ret;
}

template <int MAX_COMBO>
void MeleeComboAbility<MAX_COMBO>::Update() {
    AbilityComponent::Update();
    if(currentCooldown > 0) {
        currentCooldown--;
        if(currentCooldown == 0) {currentCombo = 0;}
    }
    if(currentCombo > 0) {
        resetCombo--;
        if(resetCombo <= 0) { currentCombo = 0; }
    }
}

#endif