#include "GameObjects/Character.h"
#include "GameObjectComponents/MapCollision.h"
#include "MeleeComboAbility.h"
#include "utils.h"

void Character::Start() {
    movement.SetCurrentMovementSpeed(characterInfo.movementSpeed);
    boxCollision.Setup(characterInfo.boxCollisionExtension);

    damageReciever.SetDamageCooldown(10);
    damageReciever.SetCharacter(this);

    AddComponent(&boxCollision);
    AddComponent(&movement);
    AddComponent(&damageReciever);

    GameObject::Start();
}

void Character::SetMapCollision(MapCollision* mc) {
    boxCollision.SetMapCollision(mc);
}

void Character::SetLayerDepth(int depth) {
    SetZOrder(1);
    GameObject::SetLayerDepth(depth);
}

void Character::Update() {
    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    UpdatePowerUpTimers();
    GameObject::Update();
}

void Character::UpdatePowerUpTimers() {
    if(atkPowerUpTime > 0) {
        atkPowerUpTime--;
        if(atkPowerUpTime <= 0) {
            SetAtkPowerUp(false);
        }
    }
    if(defPowerUpTime > 0) {
        defPowerUpTime--;
        if(defPowerUpTime <= 0) {
            SetDefPowerUp(false);
        }
    }
}

void Character::SetInputMovement(bn::fixed_point md) {
    if(damageReciever.GetAbilityInUse()) return;
    if(md.x() > 0.0f) {
        if(boxCollision.GetContact(RIGHT_COLLISION)) {
            md.set_x(0);
            movement.SetVelocityX(0);
        }
    }
    else if (md.x() < 0.0f) {
        if(boxCollision.GetContact(LEFT_COLLISION)) {
            md.set_x(0);
            movement.SetVelocityX(0);
        }
    }
    movement.SetInputMovement(md);

    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
    }
}

void Character::SetInputMovementX(bn::fixed x) {
    if(damageReciever.GetAbilityInUse()) return;
    movement.SetInputMovementX(x);
    if(boxCollision.GetContact(RIGHT_COLLISION) && movement.GetVelocity().x() > 0) {
        movement.SetVelocityX(0);
    }
    else if(boxCollision.GetContact(LEFT_COLLISION) && movement.GetVelocity().x() < 0) {
        movement.SetVelocityX(0);
    }

    movement.SetGrounded(boxCollision.GetContact(BOT_COLLISION));
    if(boxCollision.GetContact(TOP_COLLISION) && movement.GetVelocity().y() < 0) {
        movement.SetVelocityY(0);
    }
}

void Character::SetInputMovementY(bn::fixed y) {
    movement.SetInputMovementY(y);
}

void Character::GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition) {
    bool result = damageReciever.GetDamage(atkInfo, attackPosition);
    if(result) {
        characterStats.currentHealth = Utils::Max(characterStats.currentHealth - Utils::Max((atkInfo.creatorStr + atkInfo.attackPower) / characterStats.def, 1), 0);
        if(characterStats.currentHealth == 0) {
            Die();
        }
    }
}

BoxCollision* Character::GetBoxCollision() {
    return &boxCollision;
}

void Character::SetAtkPowerUp(bool powUp) {
    if(powUp) {
        characterStats.strMulti = 2;
    }
    else {
        characterStats.strMulti = 1;
    }
}

void Character::SetDefPowerUp(bool powUp) {
    if(powUp) {
        characterStats.defMulti = 2;
    }
    else {
        characterStats.defMulti = 1;
    }
}

void Character::AddAtkPowerUp() {
    SetAtkPowerUp(true);
    atkPowerUpTime = POWER_UP_TIME;
}

void Character::AddDefPowerUp() {
    SetDefPowerUp(true);
    defPowerUpTime = POWER_UP_TIME;
}