#ifndef BF_GAME_STRUCTS_H
#define BF_GAME_STRUCTS_H

enum AttackType {ATK_NONE, ATK_MELEE_SLASH, ATK_LASER_SHOT};

struct AttackInfo {
    int creatorStr;
    int attackPower;
    int impulseSpeed;
    int attackDuration;
    int attackTimeToLive;
    int projectileSpeed;
    bool destroyOnCollision;
    AttackType attackType;

    AttackInfo() {
        attackPower = 100;
        impulseSpeed = 1;
        attackDuration = 20;
        attackTimeToLive = 25;
        projectileSpeed = 10;
        attackType = AttackType::ATK_NONE;
    }

    AttackInfo(AttackType atkType, int power, int impSpeed, int duration, int atkTTL, int projectSpeed = 0, bool destroyCol = false) {
        attackType = atkType;
        attackPower = power;
        impulseSpeed = impSpeed;
        attackDuration = duration;
        attackTimeToLive = atkTTL;
        projectileSpeed = projectSpeed;
        destroyOnCollision = destroyCol;
    }
};

#endif