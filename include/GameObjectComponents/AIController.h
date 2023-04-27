#ifndef BF_AI_CONTROLLER_H
#define BF_AI_CONTROLLER_H

#include "GameObjectComponents/GameObjectComponent.h"

#include <bn_fixed_point.h>

class Character;
class Enemy;

class AIController : public GameObjectComponent{
public:
    
    AIController() = default;
    virtual ~AIController() = default;

protected:
    Character* player;
    Enemy* enemy;
    bn::fixed_point inputMovement;

public:
    virtual void Start() override;
    virtual void Update() override;

    inline void SetPlayer(Character* p) { player = p;}
    inline void SetEnemy(Enemy* e) { enemy = e;}

};

#endif