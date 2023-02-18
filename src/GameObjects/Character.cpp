#include "GameObjects/Character.h"
#include "GameObjectComponents/MapCollision.h"
#include "MeleeComboAbility.h"

void Character::Start() {
    movement.SetCurrentMovementSpeed(characterInfo.movementSpeed);
    boxCollision.Setup(characterInfo.boxCollisionExtension);

    damageReciever.SetDamageCooldown(10);

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
    GameObject::Update();
}

void Character::SetInputMovement(bn::fixed_point md) {
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
}

BoxCollision* Character::GetBoxCollision() {
    return &boxCollision;
}