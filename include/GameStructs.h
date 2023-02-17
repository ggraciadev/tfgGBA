#ifndef BF_GAME_STRUCTS_H
#define BF_GAME_STRUCTS_H

struct AttackInfo {
    int attackPower;
    int impulseSpeed;
    int attackDuration;

    AttackInfo() {
        attackPower = 100;
        impulseSpeed = 1;
        attackDuration = 20;
    }

    AttackInfo(int power, int speed, int duration) {
        attackPower = power;
        impulseSpeed = speed;
        attackDuration = duration;
    }
};

#endif