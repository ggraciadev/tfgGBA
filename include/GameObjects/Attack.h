#ifndef BF_ATTACK_H
#define BF_ATTACK_H

#include "GameObjects/GameObject.h"
#include "GameObjectComponents/BoxCollision.h"
#include "GameObjectComponents/Animator.h"
#include "GameStructs.h"
#include <bn_vector.h>

class Character;

class Attack : public GameObject {
public:
    Attack() = default;
    virtual ~Attack() = default;
    //Character(const int posX, const int posY, GameObject* _parent = nullptr);

protected:
    BoxCollision boxCollision;
    Animator<1,16> animator;
    int timeToLive = 30;
    int currentDirection = 0;
    bool componentAdded = false;
    
    AttackInfo attackInfo;
    bn::vector<Character*, 16> targets;
    Character* characterCreator;

    MapCollision* mapCollision;  

    void SetupAnimations();

public:
    virtual void Start();

    virtual void Update();
    void UpdateMovement();
    void SetAttackInfo(const AttackInfo& attackInfo);
    virtual void DoDamage(Character* other);
    void SetCharacterCreator(Character* cc);

    void SetDirection(int dir);

    void SetLayerDepth(int depth);
    void SetZOrder(char z_order);

    void SetMapCollisions(MapCollision* mCol) { mapCollision = mCol; }

};

#endif