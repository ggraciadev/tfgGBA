#ifndef BF_CHARACTER_H
#define BF_CHARACTER_H

#include "GameObjects/GameObject.h"
#include "GameObjectComponents/MovementComponent.h"
#include "GameObjectComponents/BoxCollision.h"
#include "GameObjectComponents/JumpAbility.h"
#include "GameObjectComponents/DamageRecieverAbility.h"


#define COLLISION_OFFSET_X -10
#define COLLISION_OFFSET_Y -26
#define COLLISION_WIDTH 18
#define COLLISION_HEIGHT 52
#define MOVEMENT_SPEED 1.5
#define JUMP_SPEED -4
#define MAX_JUMPS 2
#define COOLDOWN_COMBO 20

struct CharacterStats {
    int maxHealth;
    int currentHealth;
    int str;
    int strMulti;
    int def;
    int defMulti;

    CharacterStats() {
        maxHealth = 6;
        currentHealth = 6;
        str = 2;
        strMulti = 1;
        def = 2;
        defMulti = 1;
    }

    CharacterStats(int _maxHealth, int _currentHealth, int _str, int _strMulti, int _def, int _defMulti) {
        maxHealth = _maxHealth;
        currentHealth = _currentHealth;
        str = _str;
        strMulti = _strMulti;
        def = _def;
        defMulti = _defMulti;
    }
};

struct CharacterInfo {
    BoxExtension boxCollisionExtension;
    bn::fixed movementSpeed;
    int jumpSpeed;

    CharacterInfo() {
        boxCollisionExtension = BoxExtension(bn::fixed_point(COLLISION_OFFSET_X, COLLISION_OFFSET_Y), bn::fixed_point(COLLISION_WIDTH, COLLISION_HEIGHT));
        movementSpeed = MOVEMENT_SPEED;
        jumpSpeed = JUMP_SPEED;
    };
};



class Attack;

class Character : public GameObject {
public:
    Character() = default;
    ~Character() = default;
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);

protected:

    MovementComponent movement;
    BoxCollision boxCollision;
    DamageRecieverAbility damageReciever;

    CharacterInfo characterInfo;
    CharacterStats characterStats;

    void SetupAnimations() {};
    void SetupAttacks() {};

public:
    void Start();
    inline CharacterStats GetCharacterStats() const { return characterStats; }
    virtual void Update();

    virtual void SetMapCollision(MapCollision* mc);

    void SetLayerDepth(int depth);

    void SetInputMovement(bn::fixed_point md);
    void SetInputMovementX(bn::fixed x);
    void SetInputMovementY(bn::fixed y);

    inline MovementComponent* GetMovementComponent() { return &movement; }

    void UpdateAnimationState();

    virtual void GetDamage(const AttackInfo& atkInfo, const bn::fixed_point& attackPosition);
    BoxCollision* GetBoxCollision();

};

#endif